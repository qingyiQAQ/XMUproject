import pandas as pd
from time import strptime

def zerofill(n):
    if n < 10:
        return "0" + str(n)
    else:
        return str(n)

time_split = [[strptime("2019-12-26", "%Y-%m-%d"), strptime("2020-12-25", "%Y-%m-%d")],
              [strptime("2020-12-26", "%Y-%m-%d"), strptime("2021-12-25", "%Y-%m-%d")],
              [strptime("2021-12-26", "%Y-%m-%d"), strptime("2022-12-25", "%Y-%m-%d")]]

data = pd.read_excel("../data/training_data/data_year/ekg_all.xlsx", header=None)

data[0] = data[0].apply(lambda x: strptime(x, "%Y-%m-%d"))

data_2020 = data[data[0] >= time_split[0][0]]
data_2020 = data_2020[data_2020[0] <= time_split[0][1]]

data_2021 = data[data[0] >= time_split[1][0]]
data_2021 = data_2021[data_2021[0] <= time_split[1][1]]

data_2022 = data[data[0] >= time_split[2][0]]
data_2022 = data_2022[data_2022[0] <= time_split[2][1]]

data_2020[0] = data_2020[0].apply(lambda x: "-".join([str(x.tm_year), zerofill(x.tm_mon), zerofill(x.tm_mday)]))
data_2021[0] = data_2021[0].apply(lambda x: "-".join([str(x.tm_year), zerofill(x.tm_mon), zerofill(x.tm_mday)]))
data_2022[0] = data_2022[0].apply(lambda x: "-".join([str(x.tm_year), zerofill(x.tm_mon), zerofill(x.tm_mday)]))

data_2020.to_excel("../data/training_data/data_year/ekg_2020.xlsx", index=False, header=None)
data_2021.to_excel("../data/training_data/data_year/ekg_2021.xlsx", index=False, header=None)
data_2022.to_excel("../data/training_data/data_year/ekg_2022.xlsx", index=False, header=None)