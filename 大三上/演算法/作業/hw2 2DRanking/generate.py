import random

def generate_test_data(file_path, num_points=100):
    with open(file_path, 'w') as file:
        for _ in range(num_points):
            x = round(random.uniform(0, 100), 2)  # 生成 0 到 100 之間的隨機浮點數
            y = round(random.uniform(0, 100), 2)
            file.write(f"{x} {y}\n")

file_path = "D:\\Desktop\\test2.txt"
generate_test_data(file_path, num_points=100)
