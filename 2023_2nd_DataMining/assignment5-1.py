"""
2019253011
HyoungJoon Park
"""

from math import sqrt
#import numpy as np

import operator
import copy
import time
import sys

# assignment3_output.txt 데이터 받아서 클러스터 저장
def get_input_data1(filename):
    input_file = open(filename, 'r')
    clusters = dict()
    item = list()
    final_clusters = dict()
   
    i=0
    for  lines in input_file:
        
        sp = lines.strip().split()
        #print (i,list(sp[2:]))
        clusters[i] = list(sp[2:])
        final_clusters[i] = []
        i+=1

    for i in range(0,len(clusters)):
        item = clusters[i]
        for j in range (0, len(item)):

            final_clusters[i].append(int(item[j]))
   
    #print(final_clusters)
    return  final_clusters

# ground_truth.txt 데이터 받아서 클러스터 저장
def get_input_data2(filename):
    input_file = open(filename, 'r')
    datas = dict()
    ground = dict()
    ground_clusters = dict()
   
    i=0
    for  lines in input_file:
        
        sp = lines.strip().split()
        datas[i] = list(sp[1:]) #1번 행렬
        ground[i] = int(sp[0])
        ground_clusters[int(sp[0])]=[]
        i+=1
    ground_clusters[0] =[]

    for i in range(0,len(ground)):
        if ground[i] == -1:
            ground_clusters[0]. append(i)
        else :
            ground_clusters[ground[i]].append(i)
    #print (datas)
    #print (ground)    
    #print(ground_clusters)
      
    return datas, ground, ground_clusters

# assigment3_output.txt 와 ground_truth.txt 의 클러스터 결과 비교
# J-card index 사용
def calculate_jaccard_index(final_clusters, ground, datas):
    jaccard = 0

    SS=0
    DS=0
    SD=0
    DD=0

    cc=0
    pp=0

    for i in range(0,len(datas)):
        cc=0
        pp=0
       
        for j in range(0,len(datas)) :
            #print (ground[i], ground[j])
            if i!= j :
                for k in range(0,len(final_clusters)) :
                    if i in final_clusters[k] and j in final_clusters[k]:
                        cc=1
                        #print (i,j,k)

                if ground[i] == ground[j]:
                    if ground[i]!=0 and ground[j] != 0:
                        pp=1           
             
            if cc==1 and pp==1:
                SS += 1
            if cc==1 and pp==0:
                SD += 1
            if cc==0 and pp==1:
                DS += 1
            if cc==0 and pp==0:
                DD += 1    
    
    jaccard = round((SS / (SS+SD+DS)),3)
    #print (SS, SD, DS, DD)
   
    return jaccard

# assigment3_output.txt 와 ground_truth.txt 의 클러스터 결과 비교
# f-score 사용
def  calculate_fscore(ground_clusters, final_clusters):
    
    max_fscore = list()
    cluster = list()
    fsum=0

    for i in range(0, len(ground_clusters)):
        max_fscore.append(0)

    for i in range(1, len(ground_clusters)-1):
        cluster = ground_clusters[i]
        #hmean[i]=0
        for j in range(0,len(final_clusters)):
            FP=0
            FN=0
            TP=0
            precision=0
            recall=0
            
            for m in range(0, len(cluster)):
                if cluster[m] in final_clusters[j]:        
                    TP+=1
            FN = len(ground_clusters[i]) - TP       
            FP = len(final_clusters[j]) - TP
            if (TP+FN) !=0:
                recall = TP/ (TP+FN)
            if (FP+TP) != 0:
                precision= TP/(FP+TP)

            if (recall + precision) !=0 :
                fscore = 2*(recall*precision)/(recall+precision)
                if fscore> max_fscore[i]:
                    max_fscore[i]= round(fscore,3)
            #print (precision, recall)
        fsum += max_fscore[i]  
        #print (max_fscore[i])
    fmeasure =  round(fsum / len(max_fscore),3) 
    #print ("fmeasure = " + str(fmeasure))  

    return fmeasure


# 작업디렉토리에 assignment4.py, assignment3_output.txt, ground_truth.txt 를 넣습니다
# 터미널 창 입력 형식 : 
# python assignment5-1.py assignment3_output.txt ground_truth.txt
# The main function
def main():
    input_filename1 = sys.argv[1]
    input_filename2 = sys.argv[2]

    #input_filename1 = 'assignment3_output.txt'
    #input_filename2 = 'ground_truth.txt'
    
    final_clusters = get_input_data1(input_filename1)
    datas1, ground1, ground_clusters = get_input_data2(input_filename2)
    
    start_time = time.time()
    print("calculating..")
    
    jaccard = calculate_jaccard_index(final_clusters, ground1, datas1)
    fmeasure = calculate_fscore(ground_clusters, final_clusters)
    print ("Jaccard index = " + str(jaccard))
    print ("Avg of Highest F-scores = " + str(fmeasure))
    
    end_time = time.time()
    print ( "== Final Result!!")
    print('처리시간 : ', round((end_time - start_time),3), '초')


if __name__ == '__main__':
    main()
