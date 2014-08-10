import Blender
from Blender import Mesh, Scene

scn = Scene.GetCurrent()
me = Mesh.New('line')

def drawLine(mes, p1, p2):
     mes.verts.extend(p1, p2)
     mes.edges.extend(-1, -2)

drawLine(me, [0, 1, 2], [3, -2, 1])
scn.objects.new(me, 'LineObj')
