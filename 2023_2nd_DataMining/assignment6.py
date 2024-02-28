"""
2019253011
HyoungJoon Park
"""

#from math import sqrt
#from collections import deque
#import numpy as np
import collections
#import operator
#import copy
import time
import sys

def get_input_data(filename):
    input_file = open(filename, 'r')
    datas = dict()
    genes_set = set()
    i=0
    for  lines in input_file:
        sp = lines.strip().split()
        datas[i] = sorted(list(sp[0:]))
        genes_set.update(sp[0:])
        i+=1

    genes_list = list(genes_set)
    print ("total datas = " + str(len(datas)))
    return datas, genes_list

def make_adjacent_list(datas, sub_graph):
    adjacent_list= dict()
    neighbor=dict()
    temp = list()

    for i in range(0, len(sub_graph)):
        neighbor[sub_graph[i]]=[]
    temp= []

    for j in range(0, len(datas)):
            temp = datas[j]
            if temp[0] in sub_graph and temp[1] in sub_graph:
          
                    neighbor[temp[0]].append(temp[1])
     
                    neighbor[temp[1]].append(temp[0])
      
    adjacent_list = dict(sorted(neighbor.items(), key = lambda x: (x[0],x[1])))
    #print (adjacent_list)
    return adjacent_list

def bfs(adjacent_list, gene):
    visited, queue = set(), collections.deque([gene])
    visited.add(gene)
    visited_list= list()
    while queue:
        vertex = queue.popleft()
        for neighbour in adjacent_list[vertex]:
            if neighbour not in visited:
                visited.add(neighbour)
                queue.append(neighbour)

    visited_list = sorted(list(visited))
    #print ("sub_graph = "+ str(len(visited_list)))
    return visited_list

def make_graph(visited_list, adjacent_list, genes_list):
    count = len(visited_list)
    num =0
    graph= dict()
    graph[0]= visited_list
    for i in range(0, len(genes_list)):
        if (genes_list[i] not in visited_list) :
            temp_list = bfs(adjacent_list, genes_list[i])
            count += len(temp_list)
            if len(temp_list) >= 10:
                num +=1
                graph[num]= temp_list
    #print (len(adjacent_list), count)
    #print ("cluster0 = "+ str(len(graph[0])) )
    return graph

def calculate_jaccard(datas, adjacent_list, graph):
    jaccards= list()
    jaccard_list = dict()
    temp = list()
    jj=list()
    jaccard =0
    count=0
    neighbor_set1 = set()
    neighbor_set2 = set()
    jaccard_list[0]=[]
    for i in range(0, len(datas)) :
        temp= datas[i]
        #temp=sorted(datas[i])
        #print (temp)
        if (temp[0] in graph) and (temp[1] in graph):
            jj=[]
            neighbor_set1 = set(adjacent_list[temp[0]])
            neighbor_set2 = set(adjacent_list[temp[1]])
            jaccard=0
            if len(neighbor_set1 | neighbor_set2) !=0 :
                jaccard = len(neighbor_set1 & neighbor_set2) / len(neighbor_set1 | neighbor_set2)
                jj.append(temp[0])
                jj.append(temp[1])
                jj.append(jaccard)
                jaccards.append(jj)
                if jaccard == 0 :
                    count +=1
    #for i in range(0,10):
    jaccard_list = sorted(jaccards, key=lambda x : (x[2],x[0],x[1]))
        #print( jaccard_list)
    #print ("jaccard = " + str(len(jaccard_list)))
    #print ("jaccard = 0  :  " + str(count))
    return jaccard_list

def calculate_density(datas, graph):
    edges=0
    #cluster=clusters
    lists = list()
    for i in range(0, len(datas)):
        lists = datas[i]
        if (lists[0] in graph) and (lists[1] in graph):
            edges +=1
    
    vertex= len(graph)
    if vertex>1:
        density = (2*edges) / (vertex*(vertex-1))
    else :
        density = 0
   # print("edges = "+ str(edges)+ "  vertex = "+ str(len(graph))+ " density = "+ str(density)+"\n")
    return edges, density

def delete_edges_find_cluster(datas,  sub_graph, graph, cluster):
    deleted_edge_graph = list()
    #new_graph = dict()
    #cluster = dict()
    adjacent_list= make_adjacent_list(datas, sub_graph)
    jaccard = calculate_jaccard(datas, adjacent_list, sub_graph)
    #print (len(sub_graph), len(adjacent_list),len(jaccard))
    num1= len(sub_graph)
    #if num1>=0:
    for i in range(0, len(jaccard)):
            temp = jaccard[i]
        # temp[2] = jaccard_index, temp[0], [1]은 Gene
        #if temp in sub_graph : 
            if temp[0] in adjacent_list:
                if temp[1] in adjacent_list[temp[0]]:
            #print (temp[1], adjacent_list[temp[0]])
                    adjacent_list[temp[0]].remove(temp[1])
            if temp[1] in adjacent_list:
                if temp[0] in adjacent_list[temp[1]]:
                    adjacent_list[temp[1]].remove(temp[0])  
            #if num>0 :
                #print (sub_graph)
                #print(adjacent_list)
            visited_list= bfs(adjacent_list, sub_graph[0])
            num2= len(visited_list)
            #print (i,num1, num2)

            if num1- num2 >=10 : # subgraph 노드 개수 - 이미 방문한 노드 개수 >=10 , 즉 Size가 10 이상이면,
                number = len(graph)
                graph[number] = sorted(list(set(sub_graph)-set(visited_list)))
                sub_graph = sorted(visited_list)
                num1=num2
                edges, density = calculate_density(datas, graph[number])

                if density >=0.4: # Size가 10이상인 그래프에 대하여, Density Threshold 0.4 이상이면 클러스터로 판단.
                    print("graph number : " + str(number) + "  " + str(graph[number]))
                    print("edges = "+ str(edges)+ "  vertex = "+ str(len(graph[number]))+ " density = "+ str(density)+"\n")
                    cluster[len(cluster)] = graph[number]
                    #count +=1

                graph, cluster = delete_edges_find_cluster(datas,  graph[number], graph, cluster)
                #else :    
                #new_graph = graph    
            sub_graph = sorted(visited_list)
            num1=num2

    return graph, cluster

def output_to_file(filename, final_clusters):
    file = open(filename, 'w')
    lists = list()
    for i in range(0, len(final_clusters)):
        lists=[]
        lists= final_clusters[i]
        list1 = lists[1]
        #print(list1)
        strs = ""
        for j in range(0, len(list1)):
            strs += str(list1[j]) + " "
        s= str(len(list1)) + ' : ' + strs + '\n'
        print(s)
        file.write(s)
    file.close()   

# 작업디렉토리에 assignment6.py, assignment6_input.txt를 넣습니다
# 터미널 창 입력 형식 : 
# python assignment6.py assignment6_input.txt
def main():
    input_filename = sys.argv[1]
    graph= dict()
    cluster = dict()
    final_clusters=dict()
    #count =0
    #cluster[count]=[]
    output_filename = 'assignment6_output.txt'
    #input_filename = 'assignment6_input.txt'

    datas, genes_list= get_input_data(input_filename)
    start_time = time.time()
    print("calculating..")
    
    adjacent_list= make_adjacent_list(datas, genes_list)
    visited_list= bfs(adjacent_list, genes_list[0])

    graph= make_graph(visited_list, adjacent_list, genes_list)
    graph, cluster =delete_edges_find_cluster(datas,  graph[0], graph,cluster)
    #print(cluster)
    final_clusters = sorted(cluster.items(), key=lambda x: len(x[1]), reverse=True)
    #print(final_clusters)
    #for i in range (1, len(new_graph)) :
    #    graphs =delete_edges(datas,  graph[i], graph, i)

    end_time = time.time()
    print ( "== Final Result!!")
    print('처리시간 : ', end_time - start_time, '초\n')
    
    output_to_file(output_filename, final_clusters)

if __name__ == '__main__':
    main()