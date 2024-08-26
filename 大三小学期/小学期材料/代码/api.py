from flask import Flask, jsonify, request
from py2neo import Graph

from model.model import CountModel
from utils.data_load import getEvent, CountDataset
from utils.data_query import queryData
from datetime import datetime

app = Flask(__name__)
graph = Graph('bolt://localhost:7687', auth=('neo4j', '12345678'))


# 查询结点数量
@app.route('/count/node')
def nodeCount():
    query = f"""
        MATCH (n)
        RETURN sum(size(keys(n)))
        """
    result = graph.run(query).evaluate()
    return str(result)


# 查询节点类型的数量
@app.route('/count/node_types')
def nodeTypeCount():
    query = f"""
        MATCH (n)
        RETURN count(distinct labels(n))
        """
    result = graph.run(query).evaluate()
    return str(result)


# 查询关系的数量
@app.route('/count/relationship')
def relationshipCount():
    query = f"""
        MATCH ()-[r]-()
        RETURN COUNT(r)
        """
    result = graph.run(query).evaluate()
    return str(result)


# 查询关系类型的数量
@app.route('/count/relationship_types')
def relationshipTypeCount():
    query = f"""
        MATCH ()-[r]->()
        RETURN count(distinct type(r))
        """
    result = graph.run(query).evaluate()
    return str(result)


# 查询地区的数量
@app.route('/count/area')
def areaCount():
    query = f"""
        MATCH (n:Area)
        RETURN COUNT(n) as area_count
        """
    result = graph.run(query).evaluate()
    return str(result)


# 查询事件的数量
@app.route('/count/meta')
def metaCount():
    query = f"""
        MATCH (n:Meta)
        RETURN COUNT(n) as meta_count
        """
    result = graph.run(query).evaluate()
    return str(result)


# 查询该日期的所有故障事件
@app.route('/api/fault-events', methods=['GET'])
def fault_events():
    year = request.args.get('year')
    month = request.args.get('month')
    day = request.args.get('day')
    date_str = f"{year}-{month}-{day}"

    # 查询与指定日期相关联的 meta 节点
    query = f"""
           MATCH (n:Meta)
           WHERE n.time='{date_str}'
           RETURN n
           """
    metas = graph.run(query).data()

    # 用于存储所有查询结果的列表
    result = {
        "nodes": [],
        "links": []
    }

    for meta in metas:
        meta_name = meta['n']['name']
        meta_query = f"""
                    MATCH (a:Meta)-[r]-(m:Meta)
                    WHERE a.name = '{meta_name}' AND a.time='{date_str}' AND m.time='{date_str}'
                    OPTIONAL MATCH (m)-[rel]->(other_meta:Meta)
                    RETURN m, rel
                    """
        meta_results = graph.run(meta_query).data()
        for meta_result in meta_results:
            meta_result['m']['id'] = meta_result['m'].identity
            result["nodes"].append(meta_result['m'])
            if meta_result['rel'] is not None:
                result["links"].append({'source': meta_result['rel'].start_node.identity,
                                        'target': meta_result['rel'].end_node.identity})

    return jsonify(result)


# 查询与指定 Line 名称相关联的 Meta 节点
@app.route('/findByLine', methods=['GET'])
def findNodesByLine():
    line = request.args.get('line')

    # 查询与指定 Line 名称相关联的 Feeder 节点
    query = f"""
        MATCH (n:Line)-[r]-(m:Feeder)
        WHERE n.name='{line}'
        RETURN m
        """
    feeders = graph.run(query).data()

    # 用于存储所有查询结果的列表
    result = {
        "nodes": [],
        "links": []
    }

    # 循环处理每个 Feeder 节点
    for feeder in feeders:
        feeder_name = feeder['m']['name']
        meta_query = f"""
            MATCH (a:Feeder)-[r]-(m:Meta)
            WHERE a.name = '{feeder_name}'
            OPTIONAL MATCH (m)-[rel]->(other_meta:Meta)
            RETURN m, rel
            """
        meta_results = graph.run(meta_query).data()
        for meta_result in meta_results:
            meta_result['m']['id'] = meta_result['m'].identity
            result["nodes"].append(meta_result['m'])
            if meta_result['rel'] is not None:
                result["links"].append({'source': meta_result['rel'].start_node.identity,
                                        'target': meta_result['rel'].end_node.identity})
    return jsonify(result)


# FDM 预测
@app.route('/FDMpredict', methods=['GET'])
def FDMpredict():
    line = request.args.get('line')
    year = request.args.get('year')
    month = request.args.get('month')
    day = request.args.get('day')
    test_data = {'label': '', 'time': f'{year}-{month}-{day}', 'entities': [line]}
    event_lst = getEvent()

    # get test data's time and Line nodes
    test_time = test_data["time"]
    Line_lst = test_data["entities"]
    label = test_data["label"]

    # query all CEMs from different hop and time (order: full, 2020, 2021, 2022) for every model
    CEM_all, CEM_hop_all = queryData(graph, Line_lst)

    # package data for different model
    count_data = CountDataset(CEM_all, CEM_hop_all)

    # Get triples from different CEMs
    data4ekg_method = count_data.get(test_time=test_time, time_decay=True)

    # Get final result
    cm = CountModel(data4ekg_method[0])
    predict = cm.forward()

    type_rea_lst = []
    for reason in predict:
        for type in event_lst:
            if type in reason[0]:
                # type_rea_lst.append((type, reason[0].split(type)[1], reason[1]))
                type_rea_lst.append({
                    "equipment": type,
                    "reason": reason[0].split(type)[1],
                    "score": reason[1]
                })
                break

    return jsonify(type_rea_lst)


# 查询指定 Line 名称的一阶邻居（包括二阶）
@app.route('/neighbors', methods=['GET'])
def findNeighbors():
    line = request.args.get('line')

    query = f"""
        MATCH (n:Line)-[*1..2]->(m:Line)
        WHERE n.name='{line}' AND n <> m
        RETURN DISTINCT m
        """

    neighbors = graph.run(query).data()
    result = [record['m'] for record in neighbors]

    return jsonify(result)


# 查询某类型结点知识图谱
@app.route('/graph/<type>', methods=['GET'])
def findNodesByType(type):
    query = f"""
            MATCH (n:{type})
            RETURN n
            """

    result = [record['n'] for record in graph.run(query).data()]

    return jsonify(result)


# 查询某两种类型结点知识图谱
@app.route('/graph/<type1>/<type2>', methods=['GET'])
def findNodesByTwoType(type1, type2):
    global subquery
    query = f"""
            MATCH (n:{type1})
            MATCH (m:{type2})
            WITH COLLECT(DISTINCT n) AS node1,
            COLLECT(DISTINCT m) AS node2
            RETURN node1, node2
            """

    records = graph.run(query).data()

    result = {
        "links": [],
        f"{type1}": [],
        f"{type2}": []
    }

    for node in records[0]['node1']:
        node['id'] = node.identity
        result[f"{type1}"].append(node)

    for node in records[0]['node2']:
        node['id'] = node.identity
        result[f"{type2}"].append(node)

    if type1 == 'FaultyEquipmentType' and type2 == 'FaultDescription':
        subquery = f"""
                MATCH (d:{type2})<-[rel1]-(b:FaultyEquipment)-[rel2]->(a:{type1})
                RETURN DISTINCT a,d
                """
    elif type1 == 'FaultDescription' and type2 == 'FaultyEquipmentType':
        subquery = f"""
                MATCH (d:{type1})<-[rel1]-(b:FaultyEquipment)-[rel2]->(a:{type2})
                RETURN DISTINCT a,d
                """
    elif type1 == 'FaultyEquipment' and type2 == 'FaultDescriptionType':
        subquery = f"""
                MATCH (a:{type1})-[rel1]->(b:FaultDescription)-[rel2]->(d:{type2})
                RETURN DISTINCT a,d
                """
    elif type1 == 'FaultDescriptionType' and type2 == 'FaultyEquipment':
        subquery = f"""
                MATCH (a:{type2})-[rel1]->(b:FaultDescription)-[rel2]->(d:{type1})
                RETURN DISTINCT a,d
                """
    elif type1 == 'FaultDescriptionType' and type2 == 'FaultyEquipmentType':
        subquery = f"""
                MATCH path = (d:{type1})<-[rel1]-(b:FaultDescription)<-[rel2]-(c:FaultyEquipment)-[rel3]->(a:{type2})
                RETURN DISTINCT a,d
                """
    elif type1 == 'FaultyEquipmentType' and type2 == 'FaultDescriptionType':
        subquery = f"""
                MATCH path = (d:{type2})<-[rel1]-(b:FaultDescription)<-[rel2]-(c:FaultyEquipment)-[rel3]->(a:{type1})
                RETURN DISTINCT a,d
                """
    elif type1 == 'FaultDescription' and type2 == 'FaultyEquipment':
        subquery = f"""
                MATCH (a:{type2})-[rel]->(d:{type1})
                RETURN DISTINCT a,d
                """
    elif type1 == 'FaultyEquipment' and type2 == 'FaultDescription':
        subquery = f"""
                MATCH (a:{type1})-[rel]->(d:{type2})
                RETURN DISTINCT a,d
                """
    elif type1 == 'FaultyEquipment' and type2 == 'FaultyEquipmentType':
        subquery = f"""
                MATCH (a:{type1})-[rel]->(d:{type2})
                RETURN DISTINCT a,d
                """
    elif type1 == 'FaultyEquipmentType' and type2 == 'FaultyEquipment':
        subquery = f"""
                MATCH (a:{type2})-[rel]->(d:{type1})
                RETURN DISTINCT a,d
                """
    elif type1 == 'FaultDescription' and type2 == 'FaultDescriptionType':
        subquery = f"""
                MATCH (a:{type1})-[rel]->(d:{type2})
                RETURN DISTINCT a,d
                """
    elif type1 == 'FaultDescriptionType' and type2 == 'FaultDescription':
        subquery = f"""
                MATCH (a:{type2})-[rel]->(d:{type1})
                RETURN DISTINCT a,d
                """

    records = graph.run(subquery).data()

    for record in records:
        result["links"].append({'source': record['a'].identity,
                                'target': record['d'].identity})

    return jsonify(result)


# 查询四种类型结点知识图谱
@app.route('/graph/allType', methods=['GET'])
def findNodesByAllType():
    result = {
        "links": [],
        "FaultDescriptionType": [],
        "FaultDescription": [],
        "FaultyEquipmentType": [],
        "FaultyEquipment": [],
    }

    query = f"""
            MATCH (a:FaultDescriptionType)
            MATCH (b:FaultDescription)
            MATCH (c:FaultyEquipmentType)
            MATCH (d:FaultyEquipment)
            OPTIONAL MATCH (a)-[r11]-(b)
            OPTIONAL MATCH (c)-[r12]-(d)
            OPTIONAL MATCH (b)-[r2]-(d)
            WITH COLLECT(DISTINCT a) AS node1, 
            COLLECT(DISTINCT b) AS node2, 
            COLLECT(DISTINCT c) AS node3, 
            COLLECT(DISTINCT d) AS node4, 
            COLLECT(DISTINCT r11) + COLLECT(DISTINCT r12) AS rel1, 
            COLLECT(DISTINCT r2) AS rel2
            RETURN node1, node2, node3, node4, rel1, rel2
            """

    records = graph.run(query).data()

    for node in records[0]['node1']:
        node['id'] = node.identity
        result["FaultDescriptionType"].append(node)

    for node in records[0]['node2']:
        node['id'] = node.identity
        result["FaultDescription"].append(node)

    for node in records[0]['node3']:
        node['id'] = node.identity
        result["FaultyEquipmentType"].append(node)

    for node in records[0]['node4']:
        node['id'] = node.identity
        result["FaultyEquipment"].append(node)

    for rel in records[0]['rel1']:
        result["links"].append({'source': rel.start_node.identity,
                                'target': rel.end_node.identity})

    for rel in records[0]['rel2']:
        result["links"].append({'source': rel.start_node.identity,
                                'target': rel.end_node.identity})

    return jsonify(result)


# 相似事件推荐
@app.route('/recommend', methods=['GET'])
def recommend():
    line = request.args.get('line')
    year = request.args.get('year')
    month = request.args.get('month')
    day = request.args.get('day')

    # 查询与指定 Line 名称相关联的 Feeder 节点
    query = f"""
            MATCH (n:Line)-[r]-(m:Feeder)
            WHERE n.name='{line}'
            RETURN m
            """
    feeders = graph.run(query).data()

    result = []

    # 循环处理每个 Feeder 节点
    for feeder in feeders:
        feeder_name = feeder['m']['name']
        meta_query = f"""
                MATCH (a:Feeder)-[r]-(m:Meta)
                WHERE a.name = '{feeder_name}'
                RETURN m
                """
        meta_results = graph.run(meta_query).data()

        result.extend([record['m'] for record in meta_results])

    sorted_result = sorted(result, key=lambda x: abs(datetime.strptime(x['time'], '%Y-%m-%d') \
                                                     - datetime.strptime(f"{year}-{month}-{day}", '%Y-%m-%d')))

    return jsonify(sorted_result[:5])


if __name__ == '__main__':
    app.run(host='127.0.0.1', port=5000)
