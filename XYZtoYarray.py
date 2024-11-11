import json

# File paths
input_file = 'ElevationData.json'
output_file = 'y_array.json'

# Load the input data
with open(input_file, 'r') as file:
    data = json.load(file)

# Extract and round y values to the nearest 3rd decimal
y_values = [round(item['y'], 3) for item in data]

# Save y values to a new JSON file
with open(output_file, 'w') as file:
    json.dump(y_values, file, indent=4)

print(f"Y values extracted and saved to {output_file}")
