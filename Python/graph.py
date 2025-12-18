import collections
import enum
import typing


@enum.unique
class State(enum.Enum):
    UNDISCOVERED = enum.auto()
    DISCOVERED = enum.auto()
    VISITED = enum.auto()


class Edge(typing.NamedTuple):
    to: int
    # weight: T


class Vertex(typing.NamedTuple):
    edges: list[Edge]
    # label: T
    # data: T


class AdjacencyList(typing.NamedTuple):
    vertices: list[Vertex]


# I think this works correctly.
def breadth_first_traversal(graph: AdjacencyList):
    states = [State.UNDISCOVERED for _ in graph.vertices]
    for index in range(len(graph.vertices)):
        if states[index] is not State.UNDISCOVERED:
            continue
        print(f"discovered {index}")
        states[index] = State.DISCOVERED
        queue = collections.deque([index])
        while len(queue):
            index = queue.popleft()
            for edge in graph.vertices[index].edges:
                if states[edge.to] is State.UNDISCOVERED:
                    print(f"discovered {edge.to}")
                    states[edge.to] = State.DISCOVERED
                    queue.append(edge.to)
            print(f"visited {index}")
            states[index] = State.VISITED


# I'm pretty sure this isn't right; it's more like a hybrid between BFS and
# DFS.
def depth_first_traversal(graph: AdjacencyList):
    states = [State.UNDISCOVERED for _ in graph.vertices]
    for index in range(len(graph.vertices)):
        if states[index] is not State.UNDISCOVERED:
            continue
        print(f"discovered {index}")
        states[index] = State.DISCOVERED
        stack = [index]
        while stack:
            index = stack.pop()
            for edge in graph.vertices[index].edges:
                if states[edge.to] is State.UNDISCOVERED:
                    print(f"discovered {edge.to}")
                    states[edge.to] = State.DISCOVERED
                    stack.append(edge.to)
            print(f"visited {index}")
            states[index] = State.VISITED


graph = AdjacencyList(
    [
        Vertex([Edge(1), Edge(2), Edge(3)]),
        Vertex([Edge(4)]),
        Vertex([]),
        Vertex([]),
        Vertex([Edge(0)]),
    ]
)

print(graph)

print("\nBFS")
breadth_first_traversal(graph)

print("\nDFS")
depth_first_traversal(graph)
