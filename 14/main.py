import sys
import math
from queue import Queue
import matplotlib.pyplot as plt
from scipy.spatial import Voronoi, voronoi_plot_2d

EPSILON = 0.00001

def err(txt):
    print(txt, file=sys.stderr)

def distance(a, b):
    dx = a[0] - b[0]
    dy = a[1] - b[1]
    return math.sqrt(dx*dx + dy*dy)

def getPointIndex(vor, graph_children, minIndex, point):
    i,j = vor.ridge_vertices[minIndex]

    if i == -1:
        t = j
        j = i
        i = t
    
    if j == -1:
        newNodeChildren = []
        newNodeChildren.append([minIndex, distance(vor.vertices[i], point)])
        graph_children.append(newNodeChildren)

        return len(graph_children) - 1
    
    di = distance(vor.vertices[i], point)
    dj = distance(vor.vertices[j], point)
    
    pointIndex = len(graph_children)
    graph_children.append([[i, di], [j, dj]])
    graph_children[i].append([pointIndex, di])
    graph_children[j].append([pointIndex, dj])

    return pointIndex

def dijkstra(graph_children, distances, startIndex):
    q = Queue()
    q.put(startIndex)

    while not q.empty():
        index = q.get()
        q.task_done()

        for child in graph_children[index]:
            i, d = child
            totalDistance = distances[index] + d

            if distances[i] == -1 or distances[i] > totalDistance:
                q.put(i)
                distances[i] = totalDistance

def main():
    caseCount = int(input())

    for currentCase in range(1, caseCount+1):
        pointCount = int(input())

        points = []

        for currentPoint in range(1, pointCount+1):
            point = list(map(int, input().split()))
            points.append(point)
        
        radius = eval(input())
        start = list(map(eval, input().split()))
        end = list(map(eval, input().split()))
        
        # If start and end are equal 
        if start[0] == end[0] and start[1] == end[1]:
            print("Case #" + str(currentCase) + ": 0.000")
            continue
    
        vor = Voronoi(points)

        # Each child is an array of arrays [childIndex, distance]
        graph_children = []
        
        startIndex = -1
        endIndex = -1

        # Create nodes
        for i in range(0, len(vor.vertices)):
            graph_children.append([])
            
            if abs(start[0] - vor.vertices[i][0]) < EPSILON and abs(start[1] - vor.vertices[i][1]) < EPSILON:
                startIndex = i
            
            if abs(end[0] - vor.vertices[i][0]) < EPSILON and abs(end[1] - vor.vertices[i][1]) < EPSILON:
                endIndex = i

        # Create connections
        for i in range(0, len(vor.ridge_vertices)):
            v = vor.ridge_vertices[i]

            if distance(points[vor.ridge_points[i][0]], points[vor.ridge_points[i][1]])/2 >= radius:
                d = distance(vor.vertices[v[0]], vor.vertices[v[1]])
                
                if v[0] != -1 and v[1] != -1:
                    graph_children[v[0]].append([v[1], d])
                    graph_children[v[1]].append([v[0], d])
        
        # Ridge indexes
        minStartIndex = -1
        minStartDistance = -1
        minEndIndex = -1
        minEndDistance = -1

        # Find nodes
        for i in range(0, len(vor.ridge_points)):
            ia, ib = vor.ridge_points[i]
            a = points[ia]
            b = points[ib]
            
            dStart = distance(a, start)
            dEnd = distance(a, end)

            if dStart == distance(b, start):
                if minStartIndex == -1 or dStart < minStartDistance:
                    minStartIndex = i
                    minStartDistance = dStart

            if dEnd == distance(b, end):
                if minEndIndex == -1 or dEnd < minEndDistance:
                    minEndIndex = i
                    minEndDistance = dEnd
        
        if minStartIndex != -1 and minStartDistance < radius or minEndIndex != -1 and minEndDistance < radius:
            print("Case #" + str(currentCase) + ": IMPOSSIBLE")
            continue

        if startIndex == -1:
            startIndex = getPointIndex(vor, graph_children, minStartIndex, start)

        if endIndex == -1:
            endIndex = getPointIndex(vor, graph_children, minEndIndex, end)
        
        # Dijkstra
        distances = []

        for i in range(0, len(graph_children)):
            distances.append(-1)
        
        distances[startIndex] = 0

        dijkstra(graph_children, distances, startIndex)

        #voronoi_plot_2d(vor)
        #plt.show()
        if distances[endIndex] == -1:
            print("Case #" + str(currentCase) + ": IMPOSSIBLE")
        else:
            print("Case #" + str(currentCase) + ": " + "{0:.3f}".format(distances[endIndex]))



main()