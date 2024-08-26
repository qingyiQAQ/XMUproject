import pandas as pd
from time import strptime

## Get Feeder Nodes
def getFeeders(graph, Line_lst):
    # get all Feeder nodes as {f1, f2, f3, ...}
    Feeder_dict = dict()

    for line in Line_lst:
        # query feeders
        Feeder_query = "match (x:Line{name:'" + line + "'})-[r1:Interaction]-(y) return y.name as name"
        Feeders = graph.run(Feeder_query).to_data_frame()

        # remove duplicates and add to the set
        Feeder_set = set(list(Feeders["name"].values))
        Feeder_dict[line] = Feeder_set

    return Feeder_dict


## Get CEMs from Different Feeder Nodes
def getCEMs(graph, Feeder_set):

    # get all CEMs as [e1, e2, e3, time]
    CEM_lst = []
    for f in Feeder_set:

        # query TEC (e.g. Meta nodes) from all Feeder nodes
        Meta_query = "match (x:Feeder{name:'" + f + "'})-[r1:Interaction]-(y:Meta) return y.name as name, y.time as time"
        Meta_lst = graph.run(Meta_query).to_data_frame()

        # tec_name for query CEM
        Meta_name = list(Meta_lst["name"].values)
        # tec_time for CEM
        Meta_time = list(Meta_lst["time"].values)

        for name, time in zip(Meta_name, Meta_time):

            # query CEM (e.g. Cause/Fault/Consequence nodes)
            CEM_query = "match (x:Meta{name:'" + name + "'})-[r1:`Event-Subevent`]-(y) return y.name as name"
            CEM = graph.run(CEM_query).to_data_frame()

            # append CEM with its time in a list
            CEM_lst.append(list(CEM["name"].values)[::-1] + [time])

    return CEM_lst


## Get Related Line Nodes from one Line Node
def getLineRels(graph, Line_lst, topk):

    Line_rel_dict = dict()
    for line in Line_lst:

        # query related Line nodes from 0-hop Line nodes
        Line_rel_query = "match (x:Line{name:'" + line + "'})-[r1:Relatedto]->(y) return y.name as name,r1.count as count"
        Line_rel = graph.run(Line_rel_query).to_data_frame()

        # choose Top-k related Line nodes
        Line_rel_lst = list(Line_rel.sort_values(by="count", ascending=False)["name"].values)[: topk]
        Line_rel_dict[line] = set(Line_rel_lst)

    return Line_rel_dict


# Get a event chain from database
def formatData(CEM_lst):
    CEM_format_lst = []
    for i in range(CEM_lst.shape[0]):
        cem_format = {}
        cem = CEM_lst.iloc[i, :].values
        cem_format["event"] = list(cem[0:3])
        cem_format["time"] = str(cem[3]).split(" ")[0]
        CEM_format_lst.append(cem_format)
    return CEM_format_lst


## Split CEMs by different time
# def getCEMsbyTime(CEM_lst):
#
#     # define time split point
#     time_split = [[strptime("2019-12-26", "%Y-%m-%d"), strptime("2020-12-25", "%Y-%m-%d")],
#                   [strptime("2020-12-26", "%Y-%m-%d"), strptime("2021-12-25", "%Y-%m-%d")],
#                   [strptime("2021-12-26", "%Y-%m-%d"), strptime("2022-12-25", "%Y-%m-%d")]]
#
#     # define CEM list by different time
#     CEM_full_lst = CEM_lst
#     CEM_2020_lst = []
#     CEM_2021_lst = []
#     CEM_2022_lst = []
#
#     # choose data with right time and add it to list
#     for cem in CEM_lst:
#         cem_time = strptime(cem[-1], "%Y-%m-%d")
#         if (cem_time >= time_split[0][0]) and (cem_time <= time_split[0][1]):
#             CEM_2020_lst.append(cem)
#         elif (cem_time >= time_split[1][0]) and (cem_time <= time_split[1][1]):
#             CEM_2021_lst.append(cem)
#         elif (cem_time >= time_split[2][0]) and (cem_time <= time_split[2][1]):
#             CEM_2022_lst.append(cem)
#
#     return [formatData(pd.DataFrame(CEM_full_lst)),
#             formatData(pd.DataFrame(CEM_2020_lst)),
#             formatData(pd.DataFrame(CEM_2021_lst)),
#             formatData(pd.DataFrame(CEM_2022_lst))]


## Get All Data from Test Data Line Nodes
def queryData(graph, Line_lst, topk=3):

    ## Case1: Don't use TCEKG
    # get Feeder nodes
    Feeder_dict = getFeeders(graph, Line_lst)

    # get CEMs with time (time from Meta node)
    CEM_dict = {}
    for k, v in Feeder_dict.items():
        CEM_dict[k] = str(getCEMs(graph, v))

    ## Case2: Use TCEKG
    # get 1-hop Line nodes
    Line_rel_dict = getLineRels(graph, Line_lst, topk)

    # get 1-hop Feeder nodes
    Feeder_hop_dict = {}
    for k, v in Line_rel_dict.items():
        Feeder_dict_ = getFeeders(graph, v)
        Feeder_hop_lst = []
        for f in Feeder_dict_.values():
            Feeder_hop_lst += list(f)
        Feeder_hop_dict[k] = set(Feeder_hop_lst) | Feeder_dict[k]

    # get 1-hop CEMs with time (time from Meta node)
    CEM_hop_dict = {}
    for k, v in Feeder_hop_dict.items():
        CEM_hop_dict[k] = str(getCEMs(graph, v))


    return CEM_dict, CEM_hop_dict