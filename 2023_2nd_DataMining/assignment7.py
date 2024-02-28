"""
2019253011
HyoungJoon Park
"""
import collections
import time
import sys
import numpy as np

def get_input_data(filename):
    input_file = open(filename, 'r')
    data = dict()
    datas= dict()
    genes = set()
    genes_list = list()
    i=0
    for  lines in input_file:
        sp = lines.strip().split()
        data[i] = list(sp[0:])
        #print (sp[0], sp[1])
        genes.update(sp[0:])
        #genes.update(sp[1])
        i+=1

    datas = dict(sorted(data.items(), key = lambda x: (x[0],x[1])))
    genes_list = sorted(list(genes))
    print ("total datas = " + str(len(datas)))
    print ("total genes = " + str(len(genes_list))+"\n")
    #print (datas)
    return datas, genes_list

# 각 gene에 대해서 연결된 이웃을 구한다
def make_adjacent_list(datas, genes_list):
    print ("making adjacent list...\n")
    adjacent_list= dict()
    neighbor=dict()
    temp = list()

    for i in range(0, len(genes_list)):
        neighbor[genes_list[i]]=[]

    temp= []
    for j in range(0, len(datas)):
            temp = datas[j]
            neighbor[temp[0]].append(temp[1])
            neighbor[temp[1]].append(temp[0])
    adjacent_list = dict(sorted(neighbor.items(), key = lambda x: (x[0],x[1])))

    return adjacent_list

# jaccard = 두 유전자의 각 이웃의 교집합 / 각 이웃의 합집합 
# jaccard 값의 범위 : 0 ~ 1
def calculate_jaccard(genes_list,adjacent_list):
    print("making jaccard index...\n")
    jaccard_dict = dict()
    temp_dict= dict()
    jaccard =0
    neighbor_set1 = set()
    neighbor_set2 = set()
   
    for m in range(0, len(genes_list)) :
      for n in range(0, len(genes_list)):
        if m!=n :
            temp1= genes_list[m]
            temp2= genes_list[n]
    
            neighbor_set1 = set(adjacent_list[temp1])
            neighbor_set2 = set(adjacent_list[temp2])
            jaccard=0
            if len(neighbor_set1 | neighbor_set2) !=0 :
                jaccard = (len(neighbor_set1 & neighbor_set2) / len(neighbor_set1 | neighbor_set2))
                strs= temp1+","+temp2
                #print(strs)
                temp_dict[strs] = jaccard  
                
    jaccard_dict = dict(sorted(temp_dict.items(), key=lambda x :  (x[1],x[0]), reverse=True))
    
    return jaccard_dict

# density = 2 * edge / (vertices * (vertices-1))
def calculate_density(datas, density_list):
    edges=0
    lists = list()
    
    for i in datas:
        lists = datas[i]
        if (lists[0] in density_list) and (lists[1] in density_list):
            edges +=1
    
    v= len(density_list)
    if v!= 1 and v !=0:
        density = round((2*edges) / (v*(v-1)),3)
    else :
        density = 0
    
    return  density, edges, v

def make_cluster(clusters, candidate_clusters,jaccard_dict, datas):
    jaccard =0
    count=0
    countD=0
    unions = set()
    temp_list = list()
    #repl = len(clusters)
    highest_jaccard=0
    #i, j는 2개의 클러스터 그룹
    for i in range (0, len(clusters)) : 
        if highest_jaccard == 1 :
            break   
        if clusters[i] != [] :   
            for j in range(i+1, len(clusters)):
                if highest_jaccard == 1 :
                    break
                if clusters[j] != [] :  
                    # p, q는 각 클러스터의 vertex간의 jaccard 중에 가장 큰 값(highest jaccard)을 고름.
                    for p in clusters[i]:   
                        if highest_jaccard == 1 :
                            break   
                        for q in clusters[j]: 
                            temp1  = p
                            temp2= q     
                            if temp1!=temp2 :
                                    strs1= str(temp1)+","+str(temp2)
                                    jaccard = jaccard_dict[strs1]
                                    #print(jaccard)
                                    if jaccard > highest_jaccard :
                                            highest_jaccard= jaccard 
                                            unions =(set(clusters[i]+clusters[j]))
                                            t1 = clusters[i]
                                            t2 = clusters[j]
                                            if highest_jaccard == 1 :
                                                 break          
        
    print (highest_jaccard)  
    # highest_jaccard가 0.1보다 크면, 클러스터에 추가한다.       
    if highest_jaccard >0.1        :     
                
                temp_list = sorted(list(unions))
                density, edges, vertex = calculate_density(datas, temp_list)
                count+=1
                if temp_list not in clusters.values():
                    # 두 클러스터가 합쳐지면, 합쳐지기 전 2개의 클러스터를 지운다.
                    for k in clusters :
                                if t1 == clusters[k] :
                                    clusters[k] = []
                                if t2 == clusters[k] :
                                    clusters[k] = []
               
                    clusters[len(clusters)] =temp_list

                # Density가 0.4 Threshold를 만나면, candidate_cluster에 추가한다.    
                if density >=  0.4                         :
                        if temp_list not in candidate_clusters.values():
                            countD+=1
                            # 클러스터의 subset을 지운다. Superset만 남게된다.
                            for k in candidate_clusters :    
                                if t1 == candidate_clusters[k] :
                                    candidate_clusters[k] = []
                                if t2 == candidate_clusters[k] :
                                    candidate_clusters[k] = []
                        candidate_clusters[len(candidate_clusters)] = temp_list
                        print ( "\n ==> stored to candidate clusters\n")
                print ( " jaccard = "+ str(highest_jaccard)+" edge = "+str(edges)+ " vertex = "+ str(vertex)\
                       + " density = "+ str(density))
       
                print (str(t1)  + " + " )
                print (str(t2) )
                print ("= " + str(temp_list)) 
    
    print ("Total clusters = "+ str(len(clusters)) + ",  Candidate clusters = " + str(len(candidate_clusters)))
    print ("New merged_clusters = " + str(count) + ",  New candidate clusters = "+ str(countD)+"\n")   
    
      
    return clusters, candidate_clusters

# 최종적으로 size가 10 이상인 클러스터를 찾는다. 
def make_final_clusters(candidate_clusters):
    temp_clusters = dict()
    final_clusters=[]
    number=0
   
    temp_list = sorted(candidate_clusters.items(), key=lambda x: len(x[1]), reverse=True)
    
    for i in range (0, len(temp_list)) :
        if len(temp_list[i][1]) >=10 :
            temp_clusters[number]= temp_list[i][1]
            number +=1
 
    for i in range(0, len(temp_clusters)):      
       
        final_clusters.append(set(temp_clusters[i]))
  
    print ("number of final clusters : " + str(len(final_clusters))+"\n")
    return final_clusters

# final_clusters를 출력
def output_to_file(filename, final_clusters):
    file = open(filename, 'w')

    for i in range(0, len(final_clusters)):
        list1=[]
        list1= sorted(list(final_clusters[i]))
        strs = ""
        for j in range(0, len(list1)):
            strs += str(list1[j]) + " "
        s= str(len(list1)) + ' : ' + strs + '\n'
        print(s)
        file.write(s)
    file.close()   

# 작업디렉토리에 assignment7.py, assignment7_input.txt를 넣습니다
# 터미널 창 입력 형식 : 
# python assignment7.py assignment7_input.txt
def main():
    input_filename = sys.argv[1]
    output_filename = 'assignment7_output.txt'
    #input_filename = 'assignment7_input.txt'

    start_time = time.time()
    print("calculating..\n")
    clusters = dict()
    candidate_clusters=dict()

    datas, genes_list= get_input_data(input_filename)

    adjacent_list= make_adjacent_list(datas, genes_list)
    jaccard_dict = calculate_jaccard(genes_list, adjacent_list)

    for i in range (0, len(genes_list)):    
        clusters[i] = [genes_list[i]]
    
    print (len(clusters))    
    lenc= len(clusters)  
    repeat=0  
    NOchange=0
    while  True: 
        
        print( "making cluster " +str(repeat))
        repeat+=1
        clusters,candidate_clusters = make_cluster(clusters,candidate_clusters,  jaccard_dict,datas)
        if lenc == len(clusters) :
             NOchange+=1
        else :
             NOchange =0
             lenc = len(clusters)
       
        if NOchange>=10:
             break  
          
    print ("\n")
    print ( "Candidate Clusters\n")
    for k in candidate_clusters :
       # if candidate_clusters[k] != [] :
            print (k, candidate_clusters[k])
    
    print ("\nLast cluster length = " + str(len(clusters[len(clusters)-1]))\
           + " + "+str(len(clusters[len(clusters)-2])))
    print (" = " + str(len(clusters[len(clusters)-1]) +len(clusters[len(clusters)-2]))+"\n")
    print ( "== Final Result!!\n")

    final_clusters = make_final_clusters(candidate_clusters)
    end_time = time.time()
    
    print('처리시간 : ', end_time - start_time, '초\n')
    output_to_file(output_filename, final_clusters)

if __name__ == '__main__':
    main()