import itertools
from collections import Counter
from tqdm import tqdm
import pandas as pd
from utils.data_load import getVocab
from py2neo import Graph, Node, Relationship

data = pd.read_excel("../data/entity.xlsx", index_col=None)
data = [list(i)[0] for i in data.values]
data = [i for i in data if str(i) != 'nan']
data = [i.split(",") for i in data if len(i.split(",")) > 1]

relatedto_lst = []
for i in data:
    relatedto_lst += list(itertools.combinations(i, 2))

for i in data:
    relatedto_lst += list(itertools.combinations(i[::-1], 2))

edge_dict = dict(Counter(relatedto_lst))

vocab_dict = getVocab("../data/vocabulary.csv")
graph = Graph('bolt://localhost:7687', auth=('neo4j', '12345678'))

nodes_dict = {}
for key, voc in tqdm(vocab_dict.items()):
    node = Node("Line", name=voc)
    graph.create(node)
    nodes_dict[key] = node

for key, count in tqdm(edge_dict.items()):
    edge = Relationship(nodes_dict[eval(key[0])], "Relatedto", nodes_dict[eval(key[1])], count=count)
    graph.create(edge)

