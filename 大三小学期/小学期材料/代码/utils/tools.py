def logging_save(logging, log_path):
    with open(log_path, "a", encoding="utf-8") as f:
        for l in logging:
            f.write(l + "\n")
            print(l)