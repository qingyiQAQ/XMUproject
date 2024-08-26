import pandas as pd
from collections import Counter

class ConditionalProbabilityModel():
    def __init__(self, triple_part1, triple_part2):
        self.triple_part1 = triple_part1
        self.triple_part2 = triple_part2

    # Get final result from prob graph
    def forward(self):
        final_prob_dict = {}
        for i in self.triple_part1:
            ab_p = i[0].split("-")
            num_end = ab_p[1]
            for j in self.triple_part2:
                bc_p = j[0].split("-")
                num_begin = bc_p[0]
                if num_end == num_begin:
                    final_name = "-".join([ab_p[0], bc_p[0], bc_p[1]])
                    final_prob = i[1] * j[1]
                    final_prob_dict[final_name] = final_prob

        C = 0
        for c in final_prob_dict.values():
            C += c

        for k in final_prob_dict.keys():
            final_prob_dict[k] = round(final_prob_dict[k] / C, 4)

        final_prob_tuple = sorted(final_prob_dict.items(), key=lambda x: x[1], reverse=True)

        final_prob_reason = []
        for i in final_prob_tuple:
            final_prob_reason.append([i[0].split("-")[2], i[1]])

        final_prob_reason = pd.DataFrame(final_prob_reason).groupby([0]).sum().reset_index().values
        final_prob_reason = [list(i) for i in final_prob_reason]

        final_prob_reason_dict = {}
        for i in final_prob_reason:
            final_prob_reason_dict[i[0]] = i[1]

        final_prob_reason_dict = sorted(final_prob_reason_dict.items(), key=lambda x: x[1], reverse=True)
        return final_prob_reason_dict

class CountModel():
    def __init__(self, cause_lst):
        self.cause_lst = cause_lst

    def forward(self):
        counter = pd.DataFrame(self.cause_lst).groupby([0]).sum().reset_index().values
        final_count_reason_dict = dict(counter)
        final_count_reason_dict = sorted(final_count_reason_dict.items(), key=lambda x: x[1], reverse=True)
        return final_count_reason_dict





