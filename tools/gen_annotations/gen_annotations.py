import os
import sys

classes = set()
methods = set()
params = {}
returns = {}

def init_method(klass, func_name):
    classes.add(klass)
    methods.add(func_name)
    params[func_name] = []
    returns[func_name] = []

def add_params_or_returns(d, func_name, varname, ttype):
    lookups = {
        'bool': 'boolean', 'enum': 'number'
    }
    ttype = ttype.replace('_', '')
    if ttype not in ['VEC3', 'VEC4', 'QUAT']:
        if not ttype.startswith("LE3"):
            ttype = ttype.lower()
        if ttype in lookups:
            ttype = lookups[ttype]
        d[func_name].append((varname, ttype))
    else:
        if ttype == "VEC3":
            d[func_name].append((varname + '_x', 'number'))
            d[func_name].append((varname + '_y', 'number'))
            d[func_name].append((varname + '_z', 'number'))
        elif ttype == "VEC4":
            d[func_name].append((varname + '_x', 'number'))
            d[func_name].append((varname + '_y', 'number'))
            d[func_name].append((varname + '_z', 'number'))
            d[func_name].append((varname + '_w', 'number'))
        elif ttype == "QUAT":
            d[func_name].append((varname + '_w', 'number'))
            d[func_name].append((varname + '_x', 'number'))
            d[func_name].append((varname + '_y', 'number'))
            d[func_name].append((varname + '_z', 'number'))

def read_proper_functions(lines):
    func_name = ""
    for line in lines:
        line = line.strip()
        if func_name == "":
            if line.startswith("FBIND("):
                klass, name = line.replace("FBIND(", "").replace(")", "").split(",")
                klass = klass.strip(); name = name.strip()
                func_name = f"{klass}.{name}"
                init_method(klass, func_name)   
        else:
            if line.startswith("FEND()"):
                func_name = ""
            for token in ["GET_", "PUSH_"]:
                if line.startswith(token):
                    d = params if token == "GET_" else returns
                    varname = line.split('(')[1].split(',')[0].replace(')', '').strip()
                    ttype = line.split('(')[0].replace(token, "").strip()
                    if 'UDATA' in line:
                        ttype = line.split(',')[-1].replace(')', '').replace('Ptr', '').strip()
                    add_params_or_returns(d, func_name, varname, ttype)

def read_getters_setters(lines):
    for line in lines:
        if line.startswith("FBIND_"):
            ttype = line.split('(')[0].split('_')[-1].strip()
            varname = line.split(',')[1].strip()
            klass = line.split('(')[1].split(',')[0].strip()
            func_name = f"{klass}.{varname}"
            varname = varname.replace('get_', '').replace('set_', '')
            d = params if 'SETTER' in line else returns
            init_method(klass, func_name)
            params[func_name].append(("self", klass))
            add_params_or_returns(d, func_name, varname, ttype)

def read_empty_libs(lines):
    for line in lines:
        if line.startswith('LIB(') and line.endswith(')') and ',' not in line:
            klass = line.replace("LIB(", "").replace(")", "").strip()
            classes.add(klass)

def parse_binding_file(filepath):
    with open(filepath, 'r') as fp:
        lines = list(map(lambda line: line.strip().replace(';', ''), fp.readlines()))
    read_proper_functions(lines)
    read_empty_libs(lines)
    read_getters_setters(lines)

def gen_class_annotations():
    return "\n".join(["---@class $$$\n$$$ = {}".replace("$$$", klass) for klass in classes])

def gen_method_annotation(method):
    res = ""
    for varname, ttype in params[method]:
        res += f"---@param {varname} {ttype}\n"
    for _, ttype in returns[method]:
        res += f"---@return {ttype}\n"
    res += f"function {method}({', '.join(varname for varname, _ in params[method])}) end\n\n"
    return res

def gen_annotations_content(bindings_dir):
    global classes, methods
    res = "---@meta\n\n"

    for file in os.listdir(bindings_dir):
        parse_binding_file(os.path.join(bindings_dir, file))

    # Make sure everything is ordered
    classes = sorted(list(classes))
    methods = sorted(list(methods))

    res += gen_class_annotations()
    res += '\n\n--------------------------------------\n\n'
    for method in methods:
        res += gen_method_annotation(method)

    return res


if __name__ == "__main__":
    if len(sys.argv) < 3:
        raise ValueError("Too few arguments passed.")
    target_filename = sys.argv[1]
    bindings_dir = sys.argv[2]
    with open(target_filename, "w") as fp:
        fp.write(gen_annotations_content(bindings_dir))