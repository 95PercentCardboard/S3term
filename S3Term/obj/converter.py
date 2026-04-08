import argparse

def parse_obj(input_path, output_path):
    raw_vertices = []
    vertex_map = {}
    deduped_vertices = []
    edges = set()

    with open(input_path, 'r') as f:
        for line in f:
            line = line.strip()

            # parse and deduplicate vertices by position
            if line.startswith('v '):
                parts = line.split()
                x, y, z = round(float(parts[1]), 4), round(float(parts[2]), 4), round(float(parts[3]), 4)
                key = (x, y, z)
                if key not in vertex_map:
                    vertex_map[key] = len(deduped_vertices)
                    deduped_vertices.append(key)
                raw_vertices.append(vertex_map[key])

            # parse faces
            elif line.startswith('f '):
                parts = line.split()[1:]
                # remap through deduplicated vertex list
                indices = [raw_vertices[int(p.split('/')[0]) - 1] for p in parts]
                # connect each vertex to the next, and last back to first
                for i in range(len(indices)):
                    a = indices[i]
                    b = indices[(i + 1) % len(indices)]
                    edge = (min(a, b), max(a, b))
                    edges.add(edge)

    vertices = deduped_vertices

    # normalize coordinates to -0.5 to 0.5
    xs = [v[0] for v in vertices]
    ys = [v[1] for v in vertices]
    zs = [v[2] for v in vertices]
    min_x, max_x = min(xs), max(xs)
    min_y, max_y = min(ys), max(ys)
    min_z, max_z = min(zs), max(zs)
    scale = max(max_x - min_x, max_y - min_y, max_z - min_z)
    cx = (min_x + max_x) / 2
    cy = (min_y + max_y) / 2
    cz = (min_z + max_z) / 2

    with open(output_path, 'w') as f:

        f.write(f"#pragma once\n")
        f.write(f'#include "objtypes.h"\n\n')
        f.write(f"// Auto-generated from {input_path}\n")
        f.write(f"// {len(vertices)} vertices, {len(edges)} edges\n\n")

        f.write(f"//parameters to be changed by you\n\n")

        f.write(f"float rX = 0.00; //how much you rotate in radians per frame\n")
        f.write(f"float rY = 0.02; //you get the jist\n")
        f.write(f"float rZ = 0.00;\n\n")

        f.write(f"float angleX = 0.00; //these are static offsets if you model imports wrong.\n")
        f.write(f"float angleY = 0.00;\n")
        f.write(f"float angleZ = 0.00;\n\n")

        f.write(f"float fov = 2.0; //how strong perspective warping is\n\n")

        f.write(f"float zoom = 0.2; //size of model\n\n")

        f.write(f"int fps = 60; //how fast the animation runs, lower fps and heighten rotation if you experience performance impacts\n\n")

        f.write(f"int boxW = 124; //bounding box model will draw inside of\n")
        f.write(f"int boxH = 124;\n\n")
       
        f.write(F"//do not touch these\n\n")

        f.write(f"const int memUsage = {((((len(vertices)*20)+2048+4096)+1023)//1024)*1024};\n")

        f.write(f"const int vertexCount = {len(vertices)};\n")
        f.write(f"const int edgeCount = {len(edges)};\n\n")

        f.write("static points3d verts[] = {\n")
        for i, (x, y, z) in enumerate(vertices):
            nx = (x - cx) / scale
            ny = (y - cy) / scale
            nz = (z - cz) / scale
            comma = "," if i < len(vertices) - 1 else ""
            f.write(f"  {{{nx:.4f}, {ny:.4f}, {nz:.4f}}}{comma}\n")
        f.write("};\n\n")

        f.write("static edge edges[] = {\n")
        edge_list = sorted(edges)
        for i, (a, b) in enumerate(edge_list):
            comma = "," if i < len(edge_list) - 1 else ""
            f.write(f"  {{{a}, {b}}}{comma}\n")
        f.write("};\n")

    print(f"Done! {len(vertices)} vertices, {len(edges)} edges written to {output_path}")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Convert .obj file to firmware header.")
    parser.add_argument("-i", "--input", required=True, help="Path to input .obj file")
    parser.add_argument("-o", "--output", required=True, help="Path to output .h file")
    args = parser.parse_args()
    parse_obj(args.input, args.output)

