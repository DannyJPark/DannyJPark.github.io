"""
2019253011
HyoungJoon Park
"""

from math import sqrt

import operator
#import copy
import time
import sys
import random



def get_input_data(filename):
    input_file = open(filename, 'r')
    datas = dict()
   
    data_num=0
    for  lines in input_file:
        line = lines.split()
        datas[data_num] = line
       
        data_num +=1
      
    return data_num,datas


def calc_distance(datas):
    distances = list()
    lists1 = list()
    lists2 = list()
    dists= list()
    
    for i in range(0,len(datas)):
        for j in range(0,len(datas)) :
            p=0
            q=0
            r=0
            s=0
            c_distance=0
            
            if i !=j:
                lists1 = datas[i]
                lists2 = datas[j]
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
               
    distances= sorted(dists, key=operator.itemgetter(0,1))
 
    return distances

def choice_medoids1(data_num):
    
    medoids1 = list()
    medoidHx = dict()
    for i in range(0,10):
        
        random_medoids = random.randint(0,data_num-1)       
        while random_medoids in medoids1 :
            random_medoids = random.randint(0,data_num-1)
        medoids1.append(random_medoids)

    for i in range(0, len(medoids1)):
        medoidHx[i] = [medoids1[i]]
                
    return medoids1, medoidHx

def choice_medoids2(cycle,choice,medoids1, clusters1, medoidHx):
    
    medoids2 = list()
    min_distance = list()
    cluster = list()
    
    for i in range(0,len(medoids1)):
        medoids2.append(-1)
        min_distance.append(10000)
    selected=0    
    #choice+=1
    for i in range(0,len(medoids1)):
        cluster = clusters1[i]
        #print (choice, cluster, medoids1[i], medoidHx[i])
        for j in range(0, len(cluster)):
            if choice in cluster:
                if  (choice != medoids1[i]) and (choice not in medoidHx[i])  :
                    selected =1
                    medoids2[i] = choice
                    choice +=1
                    break
                else :
                    choice+=1
                    
            
        if selected == 1:
            break                 
    for j in range(0, len(medoids2)):
        if medoids2[j] == -1:
            medoids2[j]= medoids1[j]
            if choice >= 500:
                        cycle+=1
                        choice =0
        medoidHx[j].append(medoids2[j])
        
 
    return cycle,choice, medoids2, medoidHx

def make_clusters(dists,medoids):
    distances= sorted(dists, key=operator.itemgetter(0,1))
    clusters = dict()
    for i in range(0, len(medoids)):
        clusters[i]=[]
        clusters[i].append (medoids[i])
  
    non_med= 0
    max= 10000
    med_no=0
   
    for i in range(0,len(distances)) :
        if non_med != distances[i][0]:
            clusters[med_no].append(non_med)
            non_med = distances[i][0]
            max= 10000
        for j in range(0,len(medoids)):
            if  distances[i][1] == medoids[j]  :
                   if max > distances[i][2]:
                       max = distances[i][2]
                       non_med = distances[i][0]
                       med_no = j

    clusters[med_no].append(non_med)
   
    return clusters


def calculate_total_costs(dists, medoids,clusters):
    distances= sorted(dists, key=operator.itemgetter(0,1))
    cost= list()
    
    for k in range(0,len(medoids)) :
        cost.append(0)
       
    for i in range(0, len(distances)) :
        for j in range(0,len(medoids)) :
            if (distances[i][1] == medoids[j]) and (distances[i][0] in clusters[j]):
                cost[j] += distances[i][2]
    
    total_costs=0
    costs=0

    for i in range(0, len(medoids)):
        costs += cost[i]
 
    total_costs = round(costs,3)
   
    return total_costs


def output_to_file(filename, final_clusters):
   
    file = open(filename, 'w')
    lists = list()
    for i in range(0, len(final_clusters)):
        lists=[]
        lists= sorted(final_clusters[i])
        strs = ""
        for j in range(0, len(lists)):
            strs += str(lists[j]) + " "
      
        s= str(len(final_clusters[i])) + ' : ' + strs + '\n'
        print(s)
        file.write(s)
    file.close()   


# 작업디렉토리에 assignment4.py와 assignment4_input.txt를 넣습니다
# 터미널 창 입력 형식 : 
# python assignment4.py assignment4_input.txt
# The Main Fuction
def main():
    
    input_filename = sys.argv[1]

    output_filename = 'assignment4_output.txt'
    #input_filename = 'assignment4_input.txt'
    data_num, datas= get_input_data(input_filename)
    start_time = time.time()
    print("calculating..")
    distances = calc_distance(datas)
    first_medoids= list()
   
    medoids1, medoidHx = choice_medoids1(data_num)
    first_medoids = medoids1
    clusters1 =make_clusters(distances,medoids1)
    total_costs1 = calculate_total_costs(distances,medoids1, clusters1)
    
    repl =0
    changed=0
    choice=0
    cycle=0
    for i in range (1,10000):
        
        cycle, choice, medoids2, medoidHx = choice_medoids2(cycle,choice, medoids1, clusters1, medoidHx)
        clusters2 =make_clusters(distances,medoids2)
        total_costs2 = calculate_total_costs(distances,medoids2, clusters2)
        print (i, choice, repl)
        print ( "medoids1 : " + str(medoids1))
        print ( "medoids2 : " + str(medoids2))
        print ("total cost : " +str(total_costs1) + "  ,  " + str( total_costs2)+"\n")

        if choice >= 500:
            choice =0
  
        if medoids1 == medoids2 :
            print (i, choice,repl)
            print ( "initial medoids : " + str(first_medoids))
            print ( "final   medoids : " + str(medoids2))
            break

        if total_costs1 > total_costs2:
            changed =1
            medoids1=  medoids2
            clusters1 = clusters2
            total_costs1 = total_costs2
            repl += changed
            #print (i, choice,  repl)
            #choice=0
            #for j in range(0, len(medoids1)):
            #    medoidHx[j] = [medoids1[j]]
           
     
    end_time = time.time()
    print ( "== Final Result!!")
    print('처리시간 : ', round((end_time - start_time),3), '초')

    final_clusters = make_clusters(distances,medoids1)
    output_to_file(output_filename, final_clusters)
    

if __name__ == '__main__':
    main()
