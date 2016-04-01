'''
*Author: Maoxu Liu
*Description: Dijkstra algorithm. Find the shortest path from 1 to others;
*Date created: 3/31/2015
*Last improvement date: 3/31/2015
*University of Michigan - Deaborn
'''


def dijkstra(graph,start,end):
	D={}# Final distances dict
	P={}# Predecessor dict
	# Fill the dicts with default values
	for node in graph.keys():
		D[node] = -1 # Vertices are unreachable
		P[node] = "" # Vertices have no predecessors
	D[start] = 0 # The start vertex needs no more
	unseen_nodes = graph.keys() # All nodes are unseen

	while len(unseen_node) > 0:
		# Select the node with the lowest value in D (final distance)
		shortest == None
		node = ''
		for temp_node in unseen_nodes:
			if shortest == None:
				shortest = D[temp_node]
				node = temp_node
			elif D[temp_node] < shortest:
				shortest = D[temp_node]
				node = temp_node

		# Remove the selected node from unseen_nodes
		unseen_nodes.remove(node)

		# For each chile(ie: connected vertex) of the current node
		for child_node, child_value in graph[node].items():
			if D[child_node] < D[node] + child_value:
				D[child_node] = D[node] + child_value
				# To go to child_node, you have to go through node
				P[child_node] = node

	# Set a clean path
	path = []

	# We begin from the end
	node = end
	# While we are not arrived at the beginning
	while not (node == start):
		if path.count(node) == 0:
			path.insert(0,node) # insert the predecessor of the current node
			node = P[node] # The current node becomes its predessor
		else:
			break
	path.insert(0,start) # Finaly, insert the start vertex
	return path

graph = {
	'1':{'2':1,'3':2},
	'2':{'4':6,'5':12},
	'3':{'4':3,'6':4},
	'4':{'6':3,'7':15,'8':7},
	'5':{'7':7},
	'6':{'8':7,'9':15},
	'7':{'9':3},
	'8':{'9':10},
	'9':{}
}
dijkstra(graph,'1','9')