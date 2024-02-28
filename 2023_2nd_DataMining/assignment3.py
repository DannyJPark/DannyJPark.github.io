"""
2019253011
HyoungJoon Park
"""

from math import sqrt
#import numpy as np

import sys
import operator
import copy
import time

def get_input_data(filename):
    input_file = open(filename, 'r')
    data1 = dict()
   
    i=0
    for  line in input_file:
        line1 = line.split()
        data1[i] = line1
       
        i +=1
      
    return data1


def calc_distance(data1):
    distances = list()
    lists1 = list()
    lists2 = list()
    dists= list()
    sums = list()
    total_sum = list()
    total_sums = list()
    
    sum=0
    count=0
    

    for i in range(0,len(data1)):
        sum=0
        sums=[]
        for j in range(0,len(data1)) :
            p=0
            q=0
            r=0
            s=0
            c_distance=0
            
            if i !=j:
                lists1 = data1[i]
                lists2 = data1[j]
                dist = []
              
                for k in range(0,12):
                    p= lists1[k]
                    q= lists2[k]
                    r= (float(p) - float(q))**2
                    s += r
                c_distance = sqrt(s)
                
                dist.append(i)
                dist.append(j)
                dist.append(round(c_distance,3))
                dists.append(dist)
                
                count +=1
                
                sum += c_distance
        
        sums.append(i)
        sums.append(round(sum,3))
        
        total_sum.append(sums)
        sum=0
               
    distances= sorted(dists, key=operator.itemgetter(1,0))
    total_sums = sorted(total_sum, key=operator.itemgetter(1))
    #print (total_sums)
    
    return distances, total_sums


def choice_Medoids(total_sums):
    selected_Medoids = dict()
    for i in range(0,10):
        selected_Medoids[i] =[total_sums[i][0]]
   
    return selected_Medoids


def make_cluster(distances,selected_Medoids):
   
    clusters = list()
    #updated_clusters = dict()
    #for i in range(0,10):
    #    updated_clusters[i]=[]
    updated_clusters = copy.deepcopy(selected_Medoids)
  
    for i in range(0,len(distances)) :
     
       for j in range(0,len(selected_Medoids)):
   
            if  [distances[i][1]] == selected_Medoids[j]  :
                   clusters.append(distances[i])
   
    min_item = list()
    min_num = 1000
    min_distance = list()

    for k in range(0,500) :
        min_item.append(0)
        min_distance.append(min_num)

   
    for i in range(0, len(clusters)):
              if clusters[i][2] < min_distance[clusters[i][0]] :
                    min_distance[clusters[i][0]] = clusters[i][2]
                    min_item[clusters[i][0]] = clusters[i][1]
  
    for k in range(0,len(min_item)) : 
        #print (k, min_item[k])
        for j in range(0, len(selected_Medoids)) :
           
            if selected_Medoids[j] == [min_item[k]]:
                dupl=0
                for m in range(0, len(selected_Medoids)) :
                    if [k] == selected_Medoids[m]:
                        dupl+=1
                if dupl == 0:        
                    updated_clusters[j].append(k) 

    #updated_clusters = sorted(updated_cluster, key=operator.itemgetter(0))  
    #print (updated_clusters)
    
    return updated_clusters

def reassign_medoid(distances, updated_clusters, selected_Medoids):
    temp_sum = list()
    sums= list()
    clusters= updated_clusters
    dist= sorted(distances, key=operator.itemgetter(0,1))
   
    minimum= 100000
    min_sum= list()
    for k in range(0,500) :
        temp_sum.append(0)

    for i in range(0, len(dist)) :
        for j in range(0,len(clusters)) :
           
            if (dist[i][0] in clusters[j]) and (dist[i][1] in clusters[j]):
                temp_sum[dist[i][0]] += dist[i][2]


    sums = temp_sum
    for i in range(0, len (temp_sum)):
        sums[i] = round(temp_sum[i],3)
        #print (i,sums[i])
    

    for j in range(0,len(selected_Medoids)) :
        min_sum.append(minimum)

    for i in range(0, len (sums)):
        #print (i, temp_sum[i])
        for j in range(0,len(selected_Medoids)) :
            if i in clusters[j] :
                
                if sums[i] < min_sum[j]:
                    
                    min_sum[j]  = sums[i]
                    selected_Medoids[j]= [i]
                   # print (i,j, selected_Medoids[j])
                    
   
    return  selected_Medoids


def output_to_file(filename, updated_clusters):
   
    file = open(filename, 'w')
    lists = list()
    for i in range(0, len(updated_clusters)):
        lists= sorted(updated_clusters[i])
        strs = ""
        for j in range(0, len(lists)):
            strs += str(lists[j]) + " "
      
        s= str(len(updated_clusters[i])) + ' : ' + strs + '\n'
        print(s)
       
        file.write(s)
    file.close()   


# The main function
# 작업디렉토리에 assignment3.py와 assignment3_input.txt를 넣습니다
# 입력 형식 : 
# python assignment3.py assignment3_input.txt

def main():
    input_filename = sys.argv[1]

    output_filename = 'assignment3_output.txt'
    #input_filename = 'assignment3_input.txt'
    data1= get_input_data(input_filename)
    start_time = time.time()
    print("calculating..")
    distances, total_sums = calc_distance(data1)
   
    selected_Medoids = choice_Medoids(total_sums)
    print("First     K : "+ str(selected_Medoids))
    for i in range (2,21):
        updated_clusters =make_cluster(distances,selected_Medoids)
        old_Medoid = copy.deepcopy(selected_Medoids)
        selected_Medoids =reassign_medoid(distances, updated_clusters, selected_Medoids)
        print (i, "changed K : " + str(selected_Medoids))
        same=0
        for j in range (0, len(selected_Medoids)):
            if old_Medoid[j] == selected_Medoids[j]:
                same+=1
        if same == 10:
            break
        #print("             "+str(old_Medoid))

        
    end_time = time.time()
    print ( "== Final Result!!")

    updated_clusters = make_cluster(distances,selected_Medoids)
   
    print('처리시간 : ', round((end_time - start_time),3), '초')
    
    output_to_file(output_filename, updated_clusters)


if __name__ == '__main__':
    main()
