import random
import os 
def generate(file_name, num_values = 100, min_value = -100000.0, max_value = 100000.0):
    current_dir = os.path.dirname(__file__)
    file_path = os.path.join(current_dir, file_name)
    
    data = [round(random.uniform(min_value, max_value), 2) for _ in range(num_values)]
    
    with open(file_path, 'w') as f:
        for value in data:
            f.write(f"{value}\n")
generate("test1.txt", num_values = 10000)