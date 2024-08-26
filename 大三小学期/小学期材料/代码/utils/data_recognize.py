import pandas as pd
from tqdm import tqdm

from utils.data_load import getVocab

vocab_dict = getVocab()

df = pd.read_excel("./data/20221226-20230625.xlsx")
extract = df["停电线路"]
extract = list(extract.values)

extract_res = []
for i in tqdm(range(len(extract))):
    single_res = []
    for k, v in vocab_dict.items():
        if v in extract[i]:
            single_res.append(str(k))
    extract_res.append(",".join(single_res))

df["关联实体"] = pd.DataFrame(extract_res)
df.drop(["文本1_故障概述", "文本2_简单处理过程", "文本3_原因分析", "馈线名称"], axis=1, inplace=True)
df.to_excel("./data/20221226-20230625-e.xlsx")