import pandas as pd
from tqdm import tqdm
import numpy as np
from py2neo import Graph
from time import strptime
from datetime import datetime

# Get Vocabulary
def getVocab(data_path="./data/vocabulary.csv"):
    vocab = pd.read_csv(data_path, header=None)
    vocab_lst = []
    vocab_dict = {}
    for i in range(vocab.shape[0]):
        vocab_lst.append(list(vocab.iloc[i, :].values))
    for i in vocab_lst:
        vocab_dict[i[0]] = i[1]
    return vocab_dict

# Get Thick Event List
def getEvent(data_path="./data/event.txt"):
    with open(data_path, "r") as f:
        content = f.read()
    event_lst = content.split("\n")
    return event_lst

def getEntityID(data_path="./data/entity_set.txt"):
    with open(data_path, "r", encoding="utf-8") as f:
        entity_set = f.read()

    entity_lst = entity_set.split("\n")
    entity2id, id2entity = dict(), dict()
    for x, y in enumerate(entity_lst):
        entity2id[y] = x
        id2entity[x] = y

    return entity2id, id2entity


def getClassID(data_path="./data/class_set.txt"):
    with open(data_path, "r", encoding="utf-8") as f:
        class_set = f.read()

    class_lst = class_set.split("\n")
    class2id, id2class = dict(), dict()
    for x, y in enumerate(class_lst):
        class2id[y] = x
        id2class[x] = y

    return class2id, id2class

class MachineLearningDataset():
    def __init__(self, search_dict, search_hop_dict, Line_lst):
        self.search_dict = search_dict
        self.search_hop_dict = search_hop_dict
        self.Line_lst = Line_lst

    # hop decay function
    def sigma_h(self, hop, hop_decay=False):
        return 1

    # time decay function
    def sigma_t(self, time_this, time_std, time):
        if time:
            time_this = datetime.strptime(time_this, "%Y-%m-%d")
            time_std = datetime.strptime(time_std, "%Y-%m-%d")

            diff = abs((time_this - time_std).days) / 365
            # time_y = np.exp(-diff)

            return diff

        else:
            return 1

    def feature_design(self, search, time_std, time):

        Xy = []
        for l in self.Line_lst:
            features = []
            for value in eval(search[l]):
                f_time = value[-1]
                f_y = value[2]
                # f_weight = self.sigma_t(f_time, time_std, time)
                features.append([f_time, l, f_y])
            Xy += features

        return Xy


    def get(self, time_std, time_decay, hop_decay):

        # unpacking CEMs
        data = self.feature_design(self.search_dict, time_std, time_decay)
        data_hop = self.feature_design(self.search_hop_dict, time_std, time_decay)

        return data_hop, data


class ConditionalProbabilityDataset():
    def __init__(self, CEM_all, CEM_hop_all):
        self.CEM_all = CEM_all
        self.CEM_hop_all = CEM_hop_all

    # hop decay function
    def sigma_h(self, hop, hop_decay=False):
        return 1

    # time decay function
    def sigma_t(self, time_this, time_std, time):
        if time:
            time_this = datetime.strptime(time_this, "%Y-%m-%d")
            time_std = datetime.strptime(time_std, "%Y-%m-%d")

            diff = 100 * (abs((time_this - time_std).days) / 365)
            time_y = np.exp(-diff)

            return time_y

        else:
            return 1

    def get(self, test_time, time_decay, hop_decay):

        # unpacking CEMs
        CEM_full_lst, CEM_2020_lst, CEM_2021_lst, CEM_2022_lst = self.CEM_all
        CEM_hop_full_lst, CEM_hop_2020_lst, CEM_hop_2021_lst, CEM_hop_2022_lst = self.CEM_hop_all

        data_full = self.mergeData(CEM_full_lst, test_time=test_time, hop=0, time_decay=time_decay, hop_decay=hop_decay)
        data_2020 = self.mergeData(CEM_2020_lst, test_time=test_time, hop=0, time_decay=time_decay, hop_decay=hop_decay)
        data_2021 = self.mergeData(CEM_2021_lst, test_time=test_time, hop=0, time_decay=time_decay, hop_decay=hop_decay)
        data_2022 = self.mergeData(CEM_2022_lst, test_time=test_time, hop=0, time_decay=time_decay, hop_decay=hop_decay)

        data_hop_full = self.mergeData(CEM_hop_full_lst, test_time=test_time, hop=1, time_decay=time_decay, hop_decay=hop_decay)
        data_hop_2020 = self.mergeData(CEM_hop_2020_lst, test_time=test_time, hop=1, time_decay=time_decay, hop_decay=hop_decay)
        data_hop_2021 = self.mergeData(CEM_hop_2021_lst, test_time=test_time, hop=1, time_decay=time_decay, hop_decay=hop_decay)
        data_hop_2022 = self.mergeData(CEM_hop_2022_lst, test_time=test_time, hop=1, time_decay=time_decay, hop_decay=hop_decay)

        data4oth_method = [self.computeWeight(data_full),
                           self.computeWeight(data_2020),
                           self.computeWeight(data_2021),
                           self.computeWeight(data_2022)]

        data4ekg_method = [self.computeWeight(self.zipHopData(data_full, data_hop_full)),
                           self.computeWeight(self.zipHopData(data_2020, data_hop_2020)),
                           self.computeWeight(self.zipHopData(data_2021, data_hop_2021)),
                           self.computeWeight(self.zipHopData(data_2022, data_hop_2022))]

        return data4ekg_method, data4oth_method

    # Get Triples from the Format CEM
    def mergeData(self, CEM_format_lst, test_time, hop=0, time_decay=True, hop_decay=False):
        triple_part1 = []
        triple_part2 = []

        # get triples with time decay
        for cem in CEM_format_lst:
            triple_part1.append(
                ["-".join([cem["event"][0], cem["event"][1]]), round(self.sigma_t(cem["time"], test_time, time_decay), 4)])
            triple_part2.append(
                ["-".join([cem["event"][1], cem["event"][2]]), round(self.sigma_t(cem["time"], test_time, time_decay), 4)])

        # sum the same CEM
        triple_part1 = pd.DataFrame(triple_part1).groupby([0]).sum().reset_index().values
        triple_part1 = [list(i) for i in triple_part1]

        triple_part2 = pd.DataFrame(triple_part2).groupby([0]).sum().reset_index().values
        triple_part2 = [list(i) for i in triple_part2]

        # get triples with hop decay
        triple_part1 = [[i[0], round(i[1] * self.sigma_h(hop, hop_decay), 4)] for i in triple_part1]
        triple_part2 = [[i[0], round(i[1] * self.sigma_h(hop, hop_decay), 4)] for i in triple_part2]

        return [triple_part1, triple_part2]

    def zipHopData(self, data1, data2):
        data_ = []
        for x, y in zip(data1, data2):
            data_.append(x+y)

        triple_part1 = pd.DataFrame(data_[0]).groupby([0]).sum().reset_index().values
        triple_part1 = [list(i) for i in triple_part1]

        triple_part2 = pd.DataFrame(data_[1]).groupby([0]).sum().reset_index().values
        triple_part2 = [list(i) for i in triple_part2]

        return [triple_part1, triple_part2]

    def computeWeight(self, data):
        triple_part1, triple_part2 = data

        triple_part1_sum = sum([i[1] for i in triple_part1])
        triple_part2_sum = sum([i[1] for i in triple_part2])

        ### new_begin
        # graph_ab_count_by_end = [[i[0].split("-")[1], i[1]] for i in graph_ab_count]
        # graph_ab_end_name_lst = list(set([i[0] for i in graph_ab_count_by_end]))
        # graph_ab_end_count_dict = {}
        # for ab_en in graph_ab_end_name_lst:
        #     graph_ab_end_count = [i[1] for i in graph_ab_count_by_end if i[0] == ab_en]
        #     graph_ab_end_count_dict[ab_en] = sum(graph_ab_end_count)
        #
        # graph_bc_count_by_end = [[i[0].split("-")[1], i[1]] for i in graph_bc_count]
        # graph_bc_end_name_lst = list(set([i[0] for i in graph_bc_count_by_end]))
        # graph_bc_end_count_dict = {}
        # for bc_en in graph_bc_end_name_lst:
        #     graph_bc_end_count = [i[1] for i in graph_bc_count_by_end if i[0] == bc_en]
        #     graph_bc_end_count_dict[bc_en] = sum(graph_bc_end_count)
        #
        # graph_ab_weight = [[i[0], round(i[1] / graph_ab_end_count_dict[i[0].split("-")[1]], 4)] for i in graph_ab_count]
        # graph_bc_weight = [[i[0], round(i[1] / graph_bc_end_count_dict[i[0].split("-")[1]], 4)] for i in graph_bc_count]
        ### new_end

        triple_part1 = [[i[0], round(i[1] / triple_part1_sum, 4)] for i in triple_part1]
        triple_part2 = [[i[0], round(i[1] / triple_part2_sum, 4)] for i in triple_part2]

        return [triple_part1, triple_part2]

class CountDataset():
    def __init__(self, CEM_all, CEM_hop_all):
        self.CEM_all = CEM_all
        self.CEM_hop_all = CEM_hop_all

    # time decay function
    def sigma_t(self, time_this, time_std, time):
        if time:
            time_this = datetime.strptime(time_this, "%Y-%m-%d")
            time_std = datetime.strptime(time_std, "%Y-%m-%d")

            diff = abs((time_this - time_std).days) / 365
            time_y = np.exp(-diff)

            return time_y

        else:
            return 1

    def get(self, test_time, time_decay):

        # unpacking CEMs
        CEM_full_lst, _, _, _ = self.CEM_all
        CEM_hop_full_lst, _, _, _ = self.CEM_hop_all

        data_hop_full = [[i["event"][-1], round(self.sigma_t(i["time"], test_time, time_decay), 4)] for i in CEM_full_lst] +\
                        [[i["event"][-1], round(self.sigma_t(i["time"], test_time, time_decay), 4)] for i in CEM_hop_full_lst]

        data4ekg_method = [data_hop_full]

        return data4ekg_method


def getTestData(test_path="./data/20221226-20230625-e.xlsx", vocab_path="./data/vocabulary.csv"):
    data = pd.read_excel(test_path)
    vocab = getVocab(vocab_path)

    test_lst = []
    for i in tqdm(range(data.shape[0])):
        test_dict = {}
        test_data = data[["原因事件", "故障时间", "关联实体"]].iloc[i, :].values
        test_dict["label"] = test_data[0]
        test_dict["time"] = str(test_data[1]).split(" ")[0]
        er_lst = test_data[2].split(",")
        test_dict["entities"] = [vocab[int(i)] for i in er_lst]
        test_lst.append(test_dict)

    return test_lst


def getTestDataCut(cut_path, encoding):
    with open(cut_path,encoding=encoding) as f:
        content = f.read()
    return eval(content)


