from tqdm import tqdm
import pandas as pd
from py2neo import Graph, Relationship
from utils.data_load import getVocab
# graph = Graph("http://localhost:7474", user="neo4j", password="12345678", name="neo4j")
graph = Graph('bolt://localhost:7687', auth=('neo4j', '12345678'))

df = pd.read_excel("../data/20191226-20221225-e.xlsx")
vocab_dict = getVocab("../data/vocabulary.csv")

inter = df[["馈线主键", "关联实体"]]
for i in tqdm(range(inter.shape[0])):
    single_inter = inter.iloc[i,:].values
    lines = single_inter[1]
    if str(lines) != "nan":
        for j in lines.split(","):
            node1 = graph.nodes.match("Feeder", name=single_inter[0]).first()
            node2 = graph.nodes.match("Line", name=vocab_dict[eval(j)]).first()
            edge = Relationship(node1, "Interaction", node2)
            graph.create(edge)