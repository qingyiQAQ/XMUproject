from utils.data_load import getTestData

# test_data = getTestData(test_path="../data/20221226-20230625-e.xlsx", vocab_path="../data/vocabulary.csv")
with open("../data/entity_set.txt", "r", encoding="utf-8") as f:
    test_data = f.read()

print(test_data.split("\n"))
split_num = 4
split_size = int(len(test_data) / split_num)
split_index = [i*split_size for i in range(split_num)]

dir_path = "../data/entity_cut4/entity_"
file_name = ".txt"
for i in range(split_num):
    file_path = dir_path + str(i + 1) + file_name
    if i == split_num:
        break
    if i+1 == split_num:
        df = test_data[split_index[i]:]
        with open(file_path, "w", encoding="utf-8") as f:
            f.write(str(df))

    else:
        df = test_data[split_index[i]: split_index[i + 1]]
        with open(file_path, "w", encoding="utf-8") as f:
            f.write(str(df))