import json
from py2neo import Graph, Node, Relationship
from tqdm import tqdm

# data = pd.read_excel("./data/20191226-20221225-e.xlsx")
# col_need = ["元数据主键", "故障时间", "停电事件", "故障事件", "原因事件"]
# col_rename4save = ["meta", "time", "event_3", "event_2", "event_1"]
data_path = "../data/20191226-20221225-e.json"


def data2json(data, col_need, col_rename4save, save_path):
    entity_inter = list(set(data["馈线主键"].values))

    lines_info = {}
    for e_i in entity_inter:
        record = data[data["馈线主键"] == e_i]
        record = record.reset_index()
        record.drop(["index"], inplace=True, axis=1)
        record = record[col_need]
        record.columns = col_rename4save
        record["time"] = record["time"].apply(lambda x: str(x).split(" ")[0])
        nodes_info = []
        for r in range(record.shape[0]):
            nodes_info.append(dict(record.iloc[r,:]))
        lines_info[e_i] = nodes_info

    lines_info2json = json.dumps(lines_info)
    with open(save_path, "w") as f:
        f.write(lines_info2json)


def load_json(load_path):
    with open(load_path, "r") as f:
        contents = f.read()
        data = json.loads(contents)
        return dict(data)


graph = Graph('bolt://localhost:7687', auth=('neo4j', '12345678'))
data = load_json(data_path)

for k, v in tqdm(data.items()):
    # define node labels
    E4I_label = "Feeder"
    TEC_label = "Meta"
    CEM_label = ["Consequence", "Fault", "Cause"]

    # interaction entity
    IE_name = k
    node_IE = Node(E4I_label, name=IE_name)

    # temporal event chain
    nodes_TEC = []
    nodes_CEMs = []
    for c in v:
        TEC_name = c["meta"]
        TEC_time = c["time"]
        node_TEC = Node(TEC_label, name=TEC_name, time=TEC_time)
        nodes_TEC.append(node_TEC)

        # causal event model
        nodes_CEM = []
        CEM_name = [c["event_3"], c["event_2"], c["event_1"]]
        for ce_l, ce_n in zip(CEM_label, CEM_name):
            node_CEM = Node(ce_l, name=ce_n)
            nodes_CEM.append(node_CEM)
        nodes_CEMs.append(nodes_CEM)

    # every temporal event connect to its interaction entity
    relationship_ie2tec = []
    for tec in nodes_TEC:
        relationship_ie2tec.append(Relationship(node_IE, "Interaction", tec))

    # every causal event connect to its temporal event
    relationship_tec2cems = []
    for tec, cems in zip(nodes_TEC, nodes_CEMs):
        for cem in cems:
            relationship_tec2cems.append(Relationship(tec, "Event-Subevent", cem))

    # temporal event relationship
    relationship_tec2tec = []
    for i in range(len(nodes_TEC)):
        if i == len(nodes_TEC)-1:
            break
        relationship_tec2tec.append(Relationship(nodes_TEC[i], "NextEvent", nodes_TEC[i+1]))

    # causal event relationship
    relationship_cem2cem = []
    for cems in nodes_CEMs:
        relationship_cem2cem.append(Relationship(cems[0], "Causedby", cems[1]))
        relationship_cem2cem.append(Relationship(cems[1], "Causedby", cems[2]))

    # create interaction entity node
    graph.create(node_IE)

    # create temporal event nodes
    for i in nodes_TEC:
        graph.create(i)

    # create causal event nodes
    for i in nodes_CEMs:
        for j in i:
            graph.create(j)

    # create relationship between interaction entity and temporal event
    for i in relationship_ie2tec:
        graph.create(i)

    # create ralationship between temporal event and causal event
    for i in relationship_tec2cems:
        graph.create(i)

    # create relationship between temporal event and temporal event
    for i in relationship_tec2tec:
        graph.create(i)

    # create relationship between causal event and causal event
    for i in relationship_cem2cem:
        graph.create(i)






