import pandas as pd
from py2neo import Graph, Node, NodeMatcher, Relationship
from tqdm import tqdm


def extend(df):
    # 逐行读取数据
    for index, row in tqdm(df.iterrows()):
        matcher = NodeMatcher(graph)
        key = row['故障主键']
        node = matcher.match("Meta", name=key).first()

        # 添加属性
        if node is None:
            continue
        node['powerOutageStartTime'] = str(row['开始停电时间'])
        node['powerSupplyRestoreTime'] = str(row['恢复送电时间'])
        node['isLowVoltageEquipment'] = str(row['是否低压设备'])
        node['faultStartTime'] = str(row['故障发生时间'])
        node['faultEndTime'] = str(row['故障终止时间'])
        node['estimatedPowerDeliveryTime'] = str(row['预计送电时间'])
        node['protectionActionSituation'] = str(row['保护动作情况'])
        node['reclosingSituation'] = str(row['重合闸情况'])
        node['landLossSituation'] = str(row['失地情况'])
        node['isChanged'] = str(row['是否异动'])
        node['isDefective'] = str(row['是否有缺陷'])
        node['faultLevel'] = str(row['故障级别'])
        node['powerOutageCommonVariable'] = str(row['停电公变数'])
        node['powerOutageSpecificVariable'] = str(row['停电专变数'])
        graph.push(node)

        # 添加地区辖区节点
        areaNode = Node("Area", name=row['所属地区'])
        districtNode = Node("District", name=row['所属辖区'])
        if not pd.isna(row['所属地区']) and not pd.isna(row['所属辖区']):
            graph.merge(areaNode, "Area", "name")
            graph.merge(districtNode, "District", "name")
            graph.merge(Relationship(districtNode, 'BelongTo', areaNode))
            graph.merge(Relationship(node, 'HasKnowledge', districtNode))
            graph.merge(Relationship(node, 'HasKnowledge', areaNode))

        # 添加故障设备节点
        faultyEquipmentNode = Node("FaultyEquipment", name=row['故障设备'])
        faultyEquipmentTypeNode = Node("FaultyEquipmentType", name=row['故障设备分类'])
        if not pd.isna(row['故障设备分类']) and not pd.isna(row['故障设备']):
            graph.merge(faultyEquipmentNode, "FaultyEquipment", "name")
            graph.merge(faultyEquipmentTypeNode, "FaultyEquipmentType", "name")
            graph.merge(Relationship(faultyEquipmentNode, 'BelongTo', faultyEquipmentTypeNode))
            graph.merge(Relationship(node, 'HasKnowledge', faultyEquipmentNode))

        # 添加故障现象节点
        faultDescriptionTypeNode = Node("FaultDescriptionType", name=row['故障现象'])
        faultDescriptionNode = Node("FaultDescription", name=row['故障现象描述'])
        if not pd.isna(row['故障现象']) and not pd.isna(row['故障现象描述']):
            graph.merge(faultDescriptionTypeNode, "FaultDescriptionType", "name")
            graph.merge(faultDescriptionNode, "FaultDescription", "name")
            graph.merge(Relationship(faultDescriptionNode, 'BelongTo', faultDescriptionTypeNode))
            graph.merge(Relationship(node, 'HasKnowledge', faultDescriptionNode))

        if not pd.isna(row['故障设备分类']) and not pd.isna(row['故障设备']) and not pd.isna(row['故障现象']) and not pd.isna(row['故障现象描述']):
            graph.merge(Relationship(faultyEquipmentNode, 'Happen', faultDescriptionNode))


# 数据库连接
graph = Graph('bolt://localhost:7687', auth=('neo4j', '12345678'))

# 文件目录
dir = "C:\\Users\\CC507\\Desktop\\小学期材料\\事件图谱数据\\"

# 文件读取
file_path = dir + "2020年故障单.xlsx"
df = pd.read_excel(file_path, engine='openpyxl', sheet_name='清单')
extend(df)
file_path = dir + "2021年故障单.xls"
df = pd.read_excel(file_path, engine='openpyxl', sheet_name='2021剔除后故障单故障单')
extend(df)
file_path = dir + "2022年故障单.xlsx"
df = pd.read_excel(file_path, engine='openpyxl', sheet_name='故障单')
extend(df)
