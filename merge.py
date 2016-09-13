# merge.py
#
#
# Stephanie Goodale
# V00832053
#
# Accessed Bill Bird's join_grades.py

import sys
import os


def table_to_dict(T, key_column_index):
	output_dict = {}
	for row in T:
		key = row[key_column_index]
		rest_of_row = row[0:key_column_index] + row[key_column_index+1:]
		if key in output_dict:
			print('Error: Duplicate key("%s") in key column'%(key))
			exit()
		output_dict[key] = rest_of_row
	return output_dict
	
def join_grade_lists(list1, list2, id_column1, id_column2):
	if list2 == []:
		dict1 = table_to_dict(list1, id_column1)
		columns1 = len(list1[0]) - 1
		all_student_ids = set()
		for student_id in dict1:
			all_student_ids.add(student_id)
		joined_table = []
		for student_id in all_student_ids:
			if student_id not in dict1:
				entry1 = ['']*columns1	
			else:
				entry1 = dict1[student_id]
			result_row = [student_id] + (entry1)
			joined_table.append(result_row)
	#id_column = 0 #Index 0 of each row contains the student number
	else:
		dict1 = table_to_dict(list1, id_column1)
		dict2 = table_to_dict(list2, id_column2)
		columns1 = len(list1[0]) - 1
		columns2 = len(list2[0]) - 1
		all_student_ids = set()
		for student_id in dict1:
			all_student_ids.add(student_id)
		for student_id in dict2:
			all_student_ids.add(student_id)
		joined_table = []
		for student_id in all_student_ids:
			if student_id not in dict1:
				entry1 = ['']*columns1	
			else:
				entry1 = dict1[student_id]

			if student_id not in dict2:
				entry2 = ['']*columns2
			else:
				entry2 = dict2[student_id]
			result_row = [student_id] + (entry1) + (entry2)
			joined_table.append(result_row)
	return joined_table


if len(sys.argv) < 3:
	print("Usage: python3 merge.py <key column name> <file 1> <file 2> <file 3> <file 4> ...")
	exit()


column_key = sys.argv[1]

list = []
arg_num = 0
for arg in sys.argv:
	list.append(arg)
	arg_num = arg_num + 1
		
filenames = []
files = []
headers = []
headers_split = []
headers_total = []
headers_lengths = []	
	
i=0
for str in list:
	if str == sys.argv[0] or str == sys.argv[1]:
		continue
	else:
		filenames.append(str)
		try: 		
			file = open(filenames[i])
		except IOError:
			print("Error: Unable to open %s"%(filenames[i]))
			exit()
		else:
			bad_flag = 0
			files.append(file)
			for line in files[i]:
				if line.strip() != "":
					bad_flag = 1
					break
			if bad_flag == 0:
				print("Error: Invalid file '%s'. No column headings."%(filenames[i]))
				exit()
			headers.append(line)
			headers_split.append(headers[i].split(","))
			#strip column headers
			temp = []
			for word in headers_split[i]:
				new_word = word.strip()
				temp.append(new_word)
				headers_total.append(new_word)
			headers_split.remove(headers_split[i])
			headers_split.append(temp)
			temp = []
			i = i+1

for headers in headers_split:
	headers_lengths.append(len(headers))

#Find indices of column keys in files
indices = []
i=0
for arr in headers_split:
	if column_key not in arr:
		print('Error: File %s No column called "%s"'%(filenames[i], column_key))
		exit()
	else:
		indices.append(arr.index(column_key))
		i = i+1

#Get rid of duplicate headers
bad_flag = 0
bad_flag_word = ""
new_headers_total = []
new_headers_total.append(column_key)
for i in headers_total:
	if i not in new_headers_total:
		new_headers_total.append(i)
	else:
		if ((i ==  column_key) == False):
			bad_flag = 1
			bad_flag_word = i
if bad_flag == 1:
	print('Error: Column "%s" found multiple times'%(bad_flag_word))
	exit()

lines_split = []
i=0
file = files[0]
for line in file:
	if line.strip() != "":
		lines_split.append(line.split(","))
		temp = []
		for word in lines_split[i]:
			new_word = word.strip()
			temp.append(new_word)
		lines_split.remove(lines_split[i])
		lines_split.append(temp)
		if (len(lines_split[i]) == headers_lengths[0]) == False:
			print("Error: Inconsistent number of columns in %s"%(filenames[0]))
			exit()
		temp = []
		i = i+1


lines_split1 = []
i = 1
j = 0
for file in files: 
	if file is not files[0]:
		for line in file:
			if line.strip() != "":
				lines_split1.append(line.split(","))
				temp = []
				for word in lines_split1[j]:
					new_word = word.strip()
					temp.append(new_word)
				lines_split1.remove(lines_split1[j])
				lines_split1.append(temp)
				if (len(lines_split1[j]) == headers_lengths[i]) == False:
					print("Error: Inconsistent number of columns in %s"%(filenames[i]))
					exit()
				temp = []
				j = j+1
		if i == 1:
			lines_split= (join_grade_lists(lines_split, lines_split1, indices[0], indices[i]))
		else:
			lines_split= (join_grade_lists(lines_split, lines_split1, 0, indices[i]))
		lines_split1 = []
		j = 0
		i = i+1

if (len(sys.argv) == 3):
	lines_split= (join_grade_lists(lines_split, [], indices[0], 0)) 
	

print(",".join(new_headers_total))
lines_split.sort()
for line in lines_split:
	print(",".join(line))	


for file in files:
	file.close()
