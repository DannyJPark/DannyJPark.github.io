"""
YOUR NAME HERE!!!!
"""

from math import ceil
from itertools import combinations
import time
import sys

MIN_SUPPORT = 0.3
MIN_CONFIDENCE = 0.6

def get_input_data(filename):
    input_file = open(filename, 'r')
    sample_num= dict()
    disease_list= dict()
    diseaseset = set()
    disease= list()

    i=0
    for line in input_file:
        splitted = line.split()
        gene_lists = splitted[1:101]
        dis= splitted[101:]
        disease_list[i] = str(dis)
        sample_num[i] = gene_lists
        diseaseset.update(dis)
        i+=1

    disease= sorted(list(diseaseset))
   
    return sample_num, disease, disease_list


def support(sample_num, geneset, disease, disease_list):
    num= 0
    confidence=0
    support_count= list()
    support_count.append(0)
    support_count.append(0)
   
    for i in range(0, len(sample_num)): 
        num = 0 
        gene= sample_num[i]
        
        for item in geneset:
            item1 = int(item[4:6])
            item2 = str(item[7:])
            if (gene[item1].lower() == item2.lower() ) :
                num +=1
 
        if num == len(geneset) :
            confidence+=1
            for k in range(0, len(disease)):
                if disease_list[i] == ("['"+disease[k]+"']")  :
                    support_count[k] +=1

    return support_count, confidence
   

def generate_selectively_joined_itemsets(frequent_itemsets, itemset_size):
    joined_itemsets = list()
    temp_itemsets = list()
    seen_itemsets = set() 
    seen_itemlist = list(frequent_itemsets[itemset_size-1])
  
    if itemset_size < 2:
        return joined_itemsets
    
    if itemset_size >= 2:
        for itemset1 in seen_itemlist:
            for itemset2 in seen_itemlist:
                seen_itemsets = set()
                templist = list()
                if itemset1 != itemset2:
                    if itemset_size == 2:
                        templist.append(itemset1)
                        templist.append(itemset2)
                        seen_itemsets=set(templist)
                    else:    
                        seen_itemsets = set(itemset1).union(set(itemset2))
                if len(seen_itemsets) == itemset_size:
                    joined_itemlist = sorted(list(seen_itemsets))
                    if joined_itemlist not in temp_itemsets:
                        temp_itemsets.append(joined_itemlist)
    joined_itemsets = sorted(temp_itemsets)
    return joined_itemsets
    

def apply_apriori_pruning(joined_itemsets, frequent_itemsets, itemset_size):
    apriori_itemlists = list()
    candidate_genesets = list()
    #print (len(joined_itemsets))
    if itemset_size <= 2:
        return joined_itemsets

    if itemset_size > 2:     
      for itemset in joined_itemsets:
        frequents = True
        for subset in combinations(itemset,itemset_size-1):
            sublist = list(subset)
            if len(sublist) == (itemset_size-1):
                if  sublist not in frequent_itemsets[itemset_size-1]:
                    frequents= False
        if frequents == True:
            apriori_itemlists.append(itemset)
            
    candidate_genesets= sorted(apriori_itemlists)
    #print (len(candidate_genesets))
       
    return candidate_genesets 
 

def generate_candidate_genesets(frequent_itemsets, itemset_size):
    joined_itemsets = generate_selectively_joined_itemsets(frequent_itemsets, itemset_size)
    candidate_genesets = apply_apriori_pruning(joined_itemsets, frequent_itemsets, itemset_size)

    return candidate_genesets


def generate_all_frequent_geneset(sample_num, disease, disease_list, min_sup, min_con):
    frequent_genedict = dict()
    gene_size = 0
    frequent_genedict[gene_size] = list()
    frequent_genedict[gene_size].append(frozenset())

    gene_size += 1
    frequent_genedict[gene_size] = list()

    UP= dict()
    Down=dict()

    gene_list = sample_num[0]
    for i in range(0, len(gene_list)):
        UP[i]=0
        Down[i]=0
  
    for i in range(0, len(gene_list)):
        confidence1 = 0
        for j in range(0, len(sample_num)):
            if (sample_num[j][i] == 'UP'):
                    UP[i] +=1
            if (sample_num[j][i]  == 'Down') :
                    Down[i] +=1   
    
        if UP[i]>= min_sup  :
            frequent_genedict[gene_size].append("gene"+str(("0"+str(i))[-2:])+" up")

        if Down[i]>= min_sup  :
            frequent_genedict[gene_size].append("gene"+str(("0"+str(i))[-2:])+" down")

    #print ("gene size = "+ str(gene_size) + ", count = " +str(len(frequent_genedict[gene_size])))
    #print("\n")
  
    gene_size += 1

    while len(frequent_genedict[gene_size-1]) >0:
        frequent_genedict[gene_size] = list()
        candidate_genesets = generate_candidate_genesets(frequent_genedict, gene_size)
        pruned_genelist = list()
        count =0
        for geneset in candidate_genesets:
            support_count, confidence = support(sample_num, geneset, disease,disease_list)
            
            for k in range (0, len(support_count)) :       
                support_percent = (support_count[k] / len (sample_num)) * 100

                if (support_percent >=min_sup) :
                    pruned_genelist.append(geneset)
                   
        frequent_genedict[gene_size] = sorted(pruned_genelist)
        #print ("gene size = "+ str(gene_size) + ", count = " +str(count))
        #print("\n")
        gene_size += 1
    #print (frequent_genedict)   
 
    return frequent_genedict
       
def output_to_file(filename, frequent_itemsets_table, sample_num, disease, disease_list, min_sup, min_con):
   
    file = open(filename, 'w')
    for itemset_size in frequent_itemsets_table:
        # Do not print frequent itemsets of size 0 or 1
        if itemset_size == 0:
            continue
        if itemset_size == 1:
            continue
        
        # Print frequent itemsets of size 2 or larger 
        for freq_itemset in frequent_itemsets_table[itemset_size]:
            support_count, confidence = support(sample_num, freq_itemset, disease,disease_list)
            for k in range (0, len(support_count))    :       
                support_percent = (support_count[k] / len (sample_num)) * 100
                if confidence !=0:
                    confidence_percent = (support_count[k]/confidence) *len (sample_num)
                else :
                    confidence_percent = 0                
                if (support_percent >=min_sup) and (confidence_percent >= min_con): 
                    strs1 = "{"+ str(freq_itemset[0])
                    #print(strs1)
                    for i in range (1, len(freq_itemset)) :       
                        strs1 = strs1 +', '+ str(freq_itemset[i])
                        #print(strs1)
                    strs1 = strs1 + "}"
                    strs = strs1 + " → {" +  str(disease[k]) + "}: " + str(round(support_percent,2)) + "% support, "\
                               + str(round(confidence_percent,2)) + "% confidence" +"\n"
                    print (strs)
                    file.write(strs)
    file.close()


# The main function
# 작업디렉토리에 assignment8.py, assignment8_input.txt를 넣습니다
# 터미널 창 입력 형식 : 
# python assignment8.py assignment8_input.txt
def main():
    input_filename = sys.argv[1]
    output_filename = 'assignment8_output.txt'
    #input_filename = 'assignment8_input.txt'

    start_time = time.time()
    print("start..\n")
    sample_num, disease, disease_list = get_input_data(input_filename)
    min_sup = ceil(MIN_SUPPORT * len(sample_num))
    min_con = ceil(MIN_CONFIDENCE * len(sample_num))
 
    frequent_genedict = generate_all_frequent_geneset(sample_num, disease, disease_list, min_sup, min_con)
   
    output_to_file(output_filename, frequent_genedict, sample_num, disease, disease_list, min_sup, min_con)

    print ("completed!!")
    print ("result output_to_file!!")
    end_time = time.time()
    
    print('처리시간 : ', end_time - start_time, '초')

if __name__ == '__main__':
    main()