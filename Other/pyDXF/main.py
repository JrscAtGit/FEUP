import dxfgrabber

dxf = dxfgrabber.readfile("floor.dxf")
print("DXF version: {}".format(dxf.dxfversion))
header_var_count = len(dxf.header) # dict of dxf header vars
layer_count = len(dxf.layers) # collection of layer definitions
block_definition_count = len(dxf.blocks) #  dict like collection of block definitions
entity_count = len(dxf.entities) # list like collection of entities

print("Header variables: " , header_var_count)
print("Layers: " , layer_count)
print("Blocks: " , block_definition_count)
print("Entities: " , entity_count)
