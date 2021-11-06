Algorithm DFS(vertex, component, Visited, Graph)
    Visited[vertex] = true
    Add(component[vertex])
    for child in Graph[vertex]
        if(visited[child] = true) continue

        DFS(child, component, Visited, Graph)



Algorithm ConnectedComponents(G, N, E)
    // Making all visited nodes as False
    Visited[N] = False
    cc[N][N]
    currentCC[N]   

    for vertex Belongs to G.Adj[i]:
        if visited[vertex] = true
            continue
        end if

        clear(currentCC)
        DFS(vertex, currentCC, Visited)
        cc.push(currentCC)

    print(cc.size())


Time Complexity = O(V+E)

========================================================
/*
            Finding Cycle in a Graph
*/

Algorithm DFS(vertex, component, Visited, Graph, Parent)
    Visited[vertex] = true
    Add(component[vertex])
    isloopExists = False
    for child in Graph[vertex]
        if(visited[child] = true and child = Parent) return true

        isloopExists = loopExists or DFS(child, component, visited, Graph, vertex)
        DFS(child, component, Visited, Graph)

    return isloopExists



Algorithm ConnectedComponents(G, N, E)
    // Making all visited nodes as False
    Visited[N] = False
    cc[N][N]
    currentCC[N]   

    bool isloopExists = false
    for vertex Belongs to G.Adj[i]:
        if(visited[vertex]) continue
        if(DFS(vertex, component, Visited, Graph, 0))
            isloopExists = true
            break
    
    print(isloopExists)

