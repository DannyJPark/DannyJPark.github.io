"""
2019253011
HYOUNGJOON PARK (박형준)
"""

from math import ceil
from itertools import combinations
MIN_SUPPORT_PERCENT = 0.035
import operator


def get_input_data(filename):
    input_file = open(filename, 'r')
    transaction = dict()
    genes_set = set()

    for line in input_file:
        sp = line.strip().split('\t')
        transaction[sp[0]] = set(sp[1:])

        # add genes to genes_set
        genes_set.update(sp[1:])

    return transaction, genes_set


def apply_charm_algorithm(frequent_closed_itemsets, itemset_size):
    copied = frequent_closed_itemsets[itemset_size - 1].copy()
    merged_itemsets = list()
    seen_itemsets = set()
    same_tid = list()
   
    sorted(copied)
   
    for item1 in copied:
        for item2 in copied:
            #공집합 x
            if set(item1[0]) != set() and set(item2[0]) != set():
                
                templist = list()
                set1=set()
                set2=set()
                seen_itemsets=set()
                tempitem= list()
                subset = set()

                if item1[0] != item2[0]:
                    if itemset_size == 2: #사이즈 2면 그냥 합치기
                        templist.append(item1[0])
                        templist.append(item2[0])
                        subset=set(templist)

                    else:    #사이즈 2 이상이면 합집합으로 합치기
                        subset=(set(item1[0]) | set(item2[0])) 

                    if len(subset) == itemset_size:   #2개끼리 합쳤을떄, 3이되는 것만, # 3개끼리 합쳤을때> 4개가 되는것만
                        set1= set(item1[1])
                        set2= set(item2[1])
                        seen_itemsets= set1 & set2 #교집합 

                        if subset != set() :
                                tempitem.append(list(subset))
                                tempitem.append(list(seen_itemsets))
                                
                                if tempitem not in same_tid:
                                    if seen_itemsets != set():
                                        same_tid.append(tempitem)
                                # pruning non-closed itemsets
                                # t(set1) 
                                if seen_itemsets == set1:  # a,c를 합쳤는데 ac면 a를 지워
                                    if item1[0] in copied:
                                       copied.remove(item1)
                                if seen_itemsets == set2:
                                    if item2[0] in copied:
                                        copied.remove(item2)
       
    same_tid.sort()
 
    merged_itemsets = same_tid
    sorted(merged_itemsets, key=operator.itemgetter(0))
    
    #print ("itemset_size = ", itemset_size, " is_closed : ",  len(merged_itemsets))
    #print(merged_itemsets)
    return merged_itemsets


# min_support 보다 작으면 제거
def pruning_infrequent_itemsets(merged_itemsets, min_support):
    pruned_itemsets = list()
   
    p_count=0
        #cc=0
    for itemset_m in merged_itemsets:
        support_count =0
        itemset_m[1].sort()
        itemset_m[0].sort()
        support_count = len(itemset_m[1])
        
        if (support_count >= min_support) :
                if itemset_m not in pruned_itemsets:
               
                
                    p_count +=1
           
                    pruned_itemsets.append(itemset_m)
     
    sorted(pruned_itemsets)
    #print ("pruned :", len(pruned_itemsets))
    #print()
    return pruned_itemsets


def generate_all_frequent_closed_itemsets(transactions, items, min_support):
    frequent_closed_itemsets = dict()
    genedicts=dict()
    geneset=set()

    itemset_size = 0
    frequent_closed_itemsets[itemset_size] = list()
    frequent_closed_itemsets[itemset_size].append(frozenset())

    # Frequent itemsets of size 1
    itemset_size += 1
    frequent_closed_itemsets[itemset_size] = list()

    frequent_item=list()

    print ("Calculating ..\n")

    t_count=0
    for item1 in items:
        gcount =0
        support_count = 0
        geneset=set()
        itemlist= list()
        for t_items in transactions.values():
           gcount+=1
           if item1 in set(t_items):
                support_count +=1
                geneset.add(gcount)
        #print (genedicts(item1))
        if ( support_count>= min_support) : 
          itemlist.append(item1)  
          itemlist.append(geneset)
          frequent_item.append(itemlist)
          genedicts[item1]= geneset
          #print (item1, genedicts[item1])
          t_count +=1
    #print (t_count)
    frequent_closed_itemsets[itemset_size]=frequent_item
    #print(frequent_closed_itemsets[itemset_size])
    
    # Frequent itemsets of greater size
    itemset_size += 1

    while frequent_closed_itemsets[itemset_size - 1]:
        frequent_closed_itemsets[itemset_size] = list()

        # get merged_itemsets by using charm algorithm
        merged_itemsets = apply_charm_algorithm(frequent_closed_itemsets, itemset_size)
      
        # if support is greater than min_support then add to pruned_itemsets
        pruned_itemsets = pruning_infrequent_itemsets(merged_itemsets, min_support)

        # add pruned_itemsets to frequent_closed_itemsets
        frequent_closed_itemsets[itemset_size] = pruned_itemsets

        # remove non-closed item
        closed_itemset=list()
 
        for k1, v1 in frequent_closed_itemsets.items():
        # skip if the size of sets is smaller than 2
            if k1 < 2:
                continue
            #n=0   
            for item1 in v1: #똑같은게 있으면 지우기 
                    for k2, v2 in frequent_closed_itemsets.items():
                        if k2 == k1 -1:
                            closed_itemset = v2
                            for item2 in v2:
                                if (set(item2[1]) == set(item1[1])):
                                    if item2 in closed_itemset:  
                                       closed_itemset.remove(item2)
                            frequent_closed_itemsets[k2] = closed_itemset
       
        itemset_size += 1

    print (frequent_closed_itemsets)
    print ("completed!!")
    print ("result output_to_file!!")
    return frequent_closed_itemsets


def output_to_file(filename, frequent_closed_itemsets_table, transactions):
    file = open(filename, 'w')

    for dic_k, dic_v in frequent_closed_itemsets_table.items():
        # skip if the size of sets is smaller than 2
        if dic_k < 2:
            continue
        for item in dic_v:
            s = str(item[0]) + " " + str(round(len(item[1]) / len(transactions) * 100, 2)) + " % support" + str(item[1]) +"\n"
            file.write(s)
    file.close()

    file.close()

   
# The main function
def main():
    input_filename = 'assignment1_input.txt'
    output_filename = 'result.txt'
    cellular_functions, genes_set = get_input_data(input_filename)
    min_support = ceil(MIN_SUPPORT_PERCENT * len(cellular_functions))
    #print (min_support)
    frequent_closed_itemsets_table = generate_all_frequent_closed_itemsets(cellular_functions, genes_set, min_support)
    output_to_file(output_filename, frequent_closed_itemsets_table, cellular_functions)

if __name__ == '__main__':
    main()