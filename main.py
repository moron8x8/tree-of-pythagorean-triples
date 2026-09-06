import os
import subprocess
from pyvis.network import Network

def main():
    c_file_name = './generator'

    subprocess.run(["gcc", "pif3.c", "-o", "generator"], check=True)

    res = subprocess.run([c_file_name], capture_output=True, text=True)
    lines = res.stdout.strip().split("\n")
    net = Network(height='850px', width='100%', bgcolor='#000000', font_color='white', directed=True)

    net.set_options("""
        {
          "interaction": {
            "dragNodes": false
          },
          "layout": {
            "hierarchical": {
              "enabled": true,
              "direction": "UD",
              "sortMethod": "directed",
              "levelSeparation": 150,
              "nodeSpacing": 150
            }
          },
          "physics": {
            "hierarchicalRepulsion": {
              "nodeDistance": 140
            },
            "stabilization": {
              "enabled": true,
              "iterations": 1000
            }
          }
        }
        """)


    added_nodes = set()

    net.add_node("3,4,5", label='3, 4, 5', color="#ff4757", size=30)
    added_nodes.add('3,4,5')

    for line in lines:
        parent, children = line.split(';')
        if children not in added_nodes:
            label = children.replace(',', ', ')
            net.add_node(children, label=label, color="#2ed573", size=18)
            added_nodes.add(children)
        net.add_edge(parent, children, color="#57606f", width=1.5)

    output = 'index.html'
    net.save_graph(output)

    with open(output, "r", encoding="utf-8") as file:
        html_content = file.read()
        
    stop_physics_js = "\nnetwork.on('stabilizationIterationsDone', function () { network.setOptions({ physics: false }); });\n"
    html_content = html_content.replace("drawGraph();", f"drawGraph();{stop_physics_js}")
        
    with open(output, "w", encoding="utf-8") as file:
        file.write(html_content)
    

if __name__ == '__main__':
    main()