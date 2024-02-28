"""
2019253011
HYOUNGJOON PARK (박형준)
"""

from math import ceil
from itertools import combinations

MIN_SUPPORT = 0.035

# This function reads a file under filename and extracts all transactions and a set of distinct items
# param filename: The name of the input file (should provide path if necessary)
# return: A dictionary of transactions and a set of distinct items
def get_input_data(filename):
    input_file = open(filename, 'r')
    transactions = dict()
    itemset = set()
    for line in input_file:
        splitted = line.split()
        trans_id = splitted[0]
        trans_items = splitted[1:]
        transactions[trans_id] = trans_items
        itemset.update(trans_items)
    return transactions, itemset


# This function calculates support of the itemset from transactions
# param transactions: All transactions in a dictionary
# param itemset: The itemset to calculate support
# return: The support count of the itemset
def support(transactions, itemset):
    support_count = 0
    """
    FILL UP HERE!
    Calculate support of an itemset by iterating over the frequent itemsets
    """
    for t_itemsets in transactions.values(): 
        count=0  
        for item in itemset:
            for t_item in t_itemsets:
                      # print (item, t_item)
                if (item == t_item):
                     count +=1

        if count == len(itemset) :
            support_count +=1
    
    return support_count
   

# This function generates a combination from the frequent itemsets of size (itemset_size - 1) and accepts joined itemsets if they share (itemset_size - 2) items
# param frequent_itemsets: The table of frequent itemsets discovered
# param itemset_size: The size of joined itemsets
# return: All valid joined itemsets
def generate_selectively_joined_itemsets(frequent_itemsets, itemset_size):
    
    # Record seen_itemsets to prevent duplicates
    seen_itemsets = set()
    seen_itemlist = list(frequent_itemsets[itemset_size-1])
    valid_joined_itemlists = list()
    """
	FILL UP HERE!
    Try all combinations of two itemsets from the table of frequent itemsets and join the pair if they share (itemset_size - 2) items
    Add each joined itemset to the list if it is not present in the list and discard it otherwise
    """
    if itemset_size < 2:
        return valid_joined_itemlists
    
    if itemset_size >= 2:
     
        for itemset1 in frequent_itemsets[itemset_size-1]:
            for itemset2 in frequent_itemsets[itemset_size-1]:
            #print (itemset1, itemset2)
                seen_items = set()
                templist = list()
                if itemset1 != itemset2:
                    if itemset_size == 2:
                        templist.append(itemset1)
                        templist.append(itemset2)
                        seen_items=set(templist)
                       # print (seen_itemsets)
                    else:    
                        seen_items = set(itemset1).union(set(itemset2))
                #print(seen_items)
                if len(seen_items) == itemset_size:
                    joined_itemlist = list(seen_items)  
                    joined_itemlist.sort()
                    #print (joined_itemlist)
                    if joined_itemlist not in valid_joined_itemlists:
                        valid_joined_itemlists.append(joined_itemlist)

    return valid_joined_itemlists
    
 

# This function checks all the subsets of selected itemsets whether they all are frequent or not and prunes the itemset if anyone of the subsets is not frequent
# param selected_itemsets: The itemsets which are needed to be checked
# param frequent_itemsets: The table of frequent itemsets discovered
# param itemset_size: The size of intended frequent itemsets
# return: The itemsets whose all subsets are frequent
def apply_apriori_pruning(selected_itemsets, frequent_itemsets, itemset_size):
    apriori_pruned_itemlists = list()
    """
    FILL UP HERE!
	Add each itemset to the list if all of its subsets are frequent and discard it otherwise
    """
    if itemset_size <= 2:
        return selected_itemsets

    if itemset_size > 2:
      for itemset in selected_itemsets:

        # Check if all subsets are frequent
        frequents = False
        for subset in combinations(itemset,itemset_size-1):
            sublist = list(subset)
            
            for itemset1 in frequent_itemsets[itemset_size-1]:
                #print (itemset, sublist, itemset1)
                if sublist == itemset1:
                    frequents= True
                    
        if frequents == True:
            apriori_pruned_itemlists.append(itemset)
    #apriori_pruned_itemsets = selected_itemsets
    #print (apriori_pruned_itemlists)
    #return selected_itemsets
    return apriori_pruned_itemlists
    


# This function generates candidate itemsets of size (itemset_size) by selective joining and apriori pruning
# param frequent_itemsets: The table of frequent itemsets discovered
# param itemset_size: The size of intended frequent itemsets
# return: candidate itemsets formed by selective joining and apriori pruning
def generate_candidate_itemsets(frequent_itemsets, itemset_size):
    joined_itemsets = generate_selectively_joined_itemsets(frequent_itemsets, itemset_size)
    candidate_itemsets = apply_apriori_pruning(joined_itemsets, frequent_itemsets, itemset_size)
    return candidate_itemsets


# This function generates a table of itemsets with all frequent items from transactions based on a given minimum support
# param transactions: The transactions based upon which support is calculated
# param items: The unique set of items present in the transaction
# param min_sup: The minimum support to find frequent itemsets
# return: The table of all frequent itemsets of different sizes
def generate_all_frequent_itemsets(transactions, items, min_sup):

    frequent_itemsets = dict()
    itemset_size = 0
    frequent_itemsets[itemset_size] = list()
    frequent_itemsets[itemset_size].append(frozenset())
    
    # Frequent itemsets of size 1
    itemset_size += 1
    frequent_itemsets[itemset_size] = list()
    """
    FILL UP HERE!
    Find all frequent itemsets of size-1 and add them to the list
    """
    support_count = 0
    t_count =0
    frequent_item=list()
    
    for item1 in items:
        support_count = 0
        for t_items in transactions.values():
      
            for t_item in t_items:
                 if (item1 == t_item):
                    support_count +=1

        
        if (support_count >= min_sup) :
           #print ("['"+item1+"']", (support_count / len(transactions)) * 100)
           frequent_item.append(item1)
           
           t_count +=1
    frequent_itemsets[itemset_size]=frequent_item
   

    # Frequent itemsets of greater size
    itemset_size += 1

    while frequent_itemsets[itemset_size - 1]:
        frequent_itemsets[itemset_size] = list()
        candidate_itemsets = generate_candidate_itemsets(frequent_itemsets, itemset_size)
        pruned_itemset = set()
        """
        FILL UP HERE!
		Prune the candidate itemset if its support is less than minimum support
        """
        pruned_itemlist = list()

        t_count=0

        for itemset_c in candidate_itemsets:
            support_count = support(transactions, itemset_c)
            support_percent = (support_count / len(transactions)) * 100
            #print ('{0} {1:.2f}%  support\n'.format(itemset_c, support_percent)
            if (support_count >= min_sup) :
                support_percent = (support_count / len(transactions)) * 100
                print ('{0} {1:.2f}% support\n'.format(itemset_c, support_percent))
                t_count +=1
               # pruned_itemset.add(itemset_c)
                pruned_itemlist.append(itemset_c)
                #print ("passed!!")
        
        """"""
        frequent_itemsets[itemset_size] = pruned_itemlist
        print (t_count , " found ", itemset_size, "genes matched")
        print("\n")
        itemset_size += 1

    print ("completed!!")
    print ("result output_to_file!!")
    return frequent_itemsets
       

# This function writes all frequent itemsets along with their support to the output file with the given filename
# param filename: The name for the output file
# param frequent_itemsets_table: The dictionary which contains all frequent itemsets
# param transactions: The transactions from which the frequent itemsets are found
# return: void
def output_to_file(filename, frequent_itemsets_table, transactions):
    file = open(filename, 'w')
    for itemset_size in frequent_itemsets_table:

        # Do not print frequent itemsets of size 0 or 1
        if itemset_size == 0:
            continue
        if itemset_size == 1:
            continue
        
        # Print frequent itemsets of size 2 or larger 
        for freq_itemset in frequent_itemsets_table[itemset_size]:
            support_percent = (support(transactions, freq_itemset) / len(transactions)) * 100
            file.write('{0} {1:.2f}% support\n'.format(freq_itemset, support_percent))
    file.close()


# The main function
def main():
    input_filename = 'assignment1_input.txt'
    output_filename = 'assignment1_output.txt'
    cellular_functions, genes_set = get_input_data(input_filename)
    min_sup = ceil(MIN_SUPPORT * len(cellular_functions))
    """"""
    print ("start calculating...")
    print("\n")
    """"""
    frequent_itemsets_table = generate_all_frequent_itemsets(cellular_functions, genes_set, min_sup)
    output_to_file(output_filename, frequent_itemsets_table, cellular_functions)


if __name__ == '__main__':
    main()