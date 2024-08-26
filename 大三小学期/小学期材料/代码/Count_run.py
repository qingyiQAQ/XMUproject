from py2neo import Graph

import pandas as pd
from model.model import CountModel
from utils.data_load import getEvent, CountDataset
from utils.data_query import queryData

# load EKG
# graph = Graph("http://localhost:7474", user="neo4j", password="12345678", name="neo4j")
graph = Graph('bolt://localhost:7687', auth=('neo4j', '12345678'))

# load test data
test_data = {'label': '无间隙避雷器本体击穿', 'time': '2023-06-25', 'entities': ['永前线', '永兴变']}
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
            type_rea_lst.append((type, reason[0].split(type)[1], reason[1]))
            break

print(type_rea_lst)  # result format: [('裸导线', '短路、接地', 4.1755), ('未发现故障设备', '其他', 3.4087), ...]
