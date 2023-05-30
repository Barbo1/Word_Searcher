import sys
import requests
import regex as re
from bs4 import BeautifulSoup

def find_wr(e):
    """
    That function finds the part of the wordreference page that corresponds to
    the word definition.
    """
    if e.name in [None, "i", "b"]:
        s = ""
        if e.name == None:
            s = str(e)
        elif e.name in ["i", "b"] and e.string != None:
            s = e.string
        s = s.lstrip().rstrip()
        if s != "" and s[0].isalpha():
            return [s]
    elif e.name == "span":
        if 'class' not in e.attrs or e.attrs['class'] in [["rh_cat"], ["rh_def"], ["rh_sdef"], ["rh_ex"]]:
            a = []
            for i in e.children:
                a += find_wr(i)
            return a
    return []

file = open("./def.txt", 'w')
retcode = -1
if len(sys.argv) > 1:
    word = sys.argv[1]
    retcode = 0
    url = "https://www.wordreference.com/definition/"+word
    final_text = ""
    
    try:
        data = BeautifulSoup(requests.get(url).text, features="html.parser")

        #this if evaluate if the word is finded or not
        if data.find(title="No dictionary entry found for '"+word+"'") == None:
            defs = []
            for i in data.find_all(class_=["rh_sdef", "rh_def"]):
                defs = defs + find_wr(i)
            final_text = " ".join(defs)
    except Exception as e:
        print('\t exception of the type "' + str(e) + '" fount trying to find the word "'+ word +'"')
        retcode = -1
    
    file.write(final_text)
    file.flush()
file.close()
sys.exit(retcode)
    
