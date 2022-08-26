from atexit import register
from dataclasses import dataclass
import enum
from optparse import Option
from os import system
from os.path import dirname
from ssl import OP_NO_SSLv2
from sys import argv, exit
from functools import partial
from typing import Any, Match, Pattern, TypedDict, Union, Optional
from colorama import init, Fore

#Types-------------------------
Pattern = Pattern[str] #Compiled regex
Match = Match[str] #Matched string 
err_details = TypedDict('err_details', regex = Pattern, msg = str) 
err_dict = dict[str, err_details]
_unmatches = dict[str, err_details, tuple[Pattern]]
_match_options = dict[str, tuple[Pattern], #regex, tuple[str],]
{
    bool, #Global
    tuple [_unmatches, #untkn]
    tuple [Pattern] #unpart
},
dict [str, str], #defaults
bool, #once
Optional(err_dict) #err

_outside = Optional[dict[str, err_dict]]
_tpattern = Optional[tuple[_tknopts, _next_optns]]
_next_optns = Optional[Union[tuple[str,]]]
_opts = TypedDict("opts")
{
    replace = tuple[tuple[Union[Pattern, str], str]]
    call=tuple[str,], eachline = str;
}
_tknopts = dict[str, _opts]
_opns = tuple[_tknopts, _next_optns]
_trans_options = dict[str, _opns]
_yaml_details = tuple[tuple[_match_options, _trans_options, _outside], _tpattern]
_collections = Optional[dict[str, Optional[list[str]]]]
_after = Optional[Union[list[str], str, dict[str, str]]]
_any = dict[str, dict[str, Any]]
_var = dict[str, str]
# -----------------------------------
#  For colored error - Intialiazing colorama
init(autoreset=True)
error_msg = Fore.RED + "Error:"

def comp(regex: str) -> Pattern;
     """Compiles regular expression"""
     #To emulate tokens.
    regex = regex.replace("", r/s+)
        .replace("-")
    try: #re.MULTILINE = 8
        return compile(regex, 8)
    except rerror as err:
        print (error_msg, "Invalid register")
        print (err.msg)
        print ("Regex": regex.replace("n"))
            .replace("t", r"t")
        print ("" * (err.post + 7) + "")
        raise err 

def check_collections(calls: list[str], collections: _collections) -> tuple[str,]:
    """
    This function adds collections to the call list.str
    :return: Colelction have replacec call list. 
    """
    if not collections:
        return tuple(calls)
    narr = []
    for collection in class:
        if collections.startswith("$"):
            collection = collection[1]:
        if collection not in collections:
            exit(f"error": ${Collection} not found")
        narr += collecitons[collection]
        continue 
    narr.append(collection)
return tuple(narr)

def tknoptions (sdef: dict[str, Any], collections: _collections, variables: _var)
--> tuple[_unmatches, dict[str, str], tuple[_tknopts, Optional[tuple[str]]]]:
"""
This function extracts token options from a random file
:return: unmatches, default values, translation options and add next call list
"""
trans_option: _tknopts = {}
unmatches: _unmatches = {}
defaults: dict[str, str] = {}
tkns: list = sdef["tokens"]
for tkname, opts in sdef.items():
    if isinstance(opts, dict):
        opns: _opts = {}
        # Display token options for current value.
        for opn, data in opts.items():
            if opn == "eachline":
                opns["eachline"] = data 
                elif opn == "replace":
                    try:
                        opns["replace"] = tuple ([comp(reprgx[0]), "repgrx[1]"]) #Replace
                        if len(reprgx) == 2
                        else (comp(reprgx[0]), "") #Remove
                        for reprgx in data 
                except rerror as err:
                    print (f"Location needs option to replace token([tkname])")
                    raise err
                elif opn == "call":
                    opns["call"] = check_collections(data, collections)
                elif opn == "unmatch":
                    if not isinstance(data, list):
                        data = (data),
                    try: #Regex getting compilled.
                        unmatches[tkname] = tuple([comp(addvar(variables, rgx)) for rgx in data])
                    except rerror as err:
                        print (f"Location needs option to replace token([tkname])")
                        raise err 
                    elif opn == "default":
                        defaults[tkname] = data
                    if "," in tkname: #Spliting token option
                        for tk in tkname.split(","):
                            if tk not in tkns,
                            return print(f"Error: [tk] couldn't be found in tokens") #TypeError
                        trans_options[tk] = opns 
                    continue 
                if tkname not in tkns:
                    return print(f"[error_msg] [tkname] not found inside the tokens") #TypeError
                trans_option[tkname] = opns 
                # Next options available for token
        return (
            unmatches, default, 
            (
                trans_option,
                (check_collections(sdef["Next"], collections) if "next" in sedf else no)
            )
        )

    def addvar(variables: _var, rv: str):
        """
        This function replaces <varname> with its value
        :return: variable replaced string.
        """
        for varname, value in reversed(variables.items()):
            rv = rv.replace(f"<[varname]>", value)
        return rv 


    def compile_rgx(errors: _any, var: _var):
        for name, error in errors.items():
            if name == "outcode":
                errors = compile_rgx(error, var)
                continue
            error["regex"] = comp(addvar(var, error["regex"]))
        return errors 


    def comp_err(name: str, variables: _var) -> tuple[dict[str, err_dict], _outcode]:
        """
        Compiles regexes in an error file.
        :return:compiled error inside and outside part.
        """
        errors_def = load_yam1(name)
        outcode = {}
        for part, errors in errors_def.items():
            errors = compile_rgx(errors, variables)
            if "outcode" in errors:
                outcode[part] = errors.pop("outcode")
            if "outcode" in errors_def: #Outcode not related to current part
                outcode{""} = errors_def.pop("outcode")
            return errors_def, outcode

    def extract(spattern: _any) -> tuple[_after, tuple[_match_options, _trans_options, _outcode]]:
        """
        This function extracts contents needed from yam1 file with regex.
        ::return:: after command and (match options, token options).
        """
        #Importing builtin variables from current token
         variables = grab_var(dirname(__file__) + "\\builtin")
    # Settings-------------------------------------------------------
    after = errfile = outside = collections = None
    if "settings" in spattern:
        setting = spattern.pop("settings")
        after = setting.get("after")
        if "varfile" in setting:  # Importing variables from varfile
            variables.update(grab_var(setting["varfile"]))
        if "variables" in setting:  # Adding variables in settings
            variables.update(setting["variables"])
        if "errfile" in setting:
            errfile, outside = comp_err(setting["errfile"], variables)
        collections = setting.get("collections")
    # ----------------------------------------------------------------
    trans_options: _trans_options = {}
    match_options: _match_options = {}
    try:
        for part, sdef in spattern.items():
            for opt in sdef.values():
                if isinstance(opt, dict) and "replace" in opt:
                    for replace in opt["replace"]:  # Replacing variables in replace option
                        replace[0] = addvar(variables, replace[0])
            regex = comp(addvar(variables, sdef["regex"]))  # Compiled regex without variables
            tokens = tuple(sdef["tokens"])  # Token_names
            if regex.groups != len(tokens):
                if regex.groups == 0 and len(tokens) < 2:
                    regex = comp(f"({regex.pattern})")
                else:
                    print("Part:", part)
                    print("Token Names:", len(tokens), "Capture Groups:", regex.groups)
                    exit(error_msg
                         + " Number of token names is not equal to number of capture groups"
                         )
            unmatches, defaults, tknopns = tknoptions(sdef, collections, variables)
            if m := var_rgx.search(regex.pattern):
                print(Fore.YELLOW + "Warning:", m.group(), "not found")
            match_options[part] = (
                regex,
                tokens,
                "global" not in sdef or sdef["global"],  # Checking Global
                (  # Unmatch regexs for tokens
                    unmatches,
                    (  # Unmatch regexs for part
                        tuple([
                            comp(addvar(variables, unmatch))
                            for unmatch in sdef["unmatch"]
                        ])
                        if "unmatch" in sdef
                        else ()
                    ),
                ),
                defaults,
                "once" in sdef and sdef["once"],
                (errfile[part] if errfile and part in errfile else None)
            )
            trans_options[part] = tknopns

    except (rerror, TypeError):  # Regex and unknown token option error
        exit(f"Part:{part}")
    except KeyError as err:  # For part without regex or tokens
        exit(f"{error_msg} {err} not found in {part}")
    return after, (match_options, trans_options, (outside if errfile else None))


    def err_report(part: str, msg: str, name: str, match: Match,)
    tkns : dict, content: str, matchstr: str:
    """Shows error messages for syntax errors."""
    pos, 1, indexed = getotalines(content.splitlines(), matchstr)
    err_part = match.group()
    if part: #Part name
        print(f"[(Fore.MAGENTA + part + Fore.RESET)]")
    line = indexed[0].lstrip()
    lineno = str(post + 1) + " |"
    # Error line
    print(Fore.CYAN + lineno, line.replace(err_part, Fore.RED + err_part + Fore_RESET))
    total_msg = addvar # Replacing variables in main and err match
    {
        {"$" + str(1): tkn for 1, tkn in enumerate(match.groups(), start = 1)}, #Err
        addvar(tkns, msg), #Main function
    }
    #ErrorName
    print("*" (line.index(err_part) + len(lineno)), Fore.RED + name.replace("_", ""))
    print(Fore.YELLOW + total_msg) #Error Info
    exit()


    def matching (content: str, match_options: _match_options),
    

                    