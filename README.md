# Word_Searcher
This is an application that search words in internet, presicely in **WordReference** dictionary. It search an initial word and store the ones in the definition in a **WordSet**(Is the same structure that in the Libraries repository). Recursibely do this process the quantity of times you need. this process last with two text files: *words.txt* that contain the words finded in the process, and *error.txt* get the words that triggers a problem in the searching. Is useful to now that, because **WordReference** have a *"general ditcionary"*(lets say, one that have words that don't belong to the lenguage), there could be some inexistent words in the *words.txt* file. Some effort is made by the program to get this inexistent words out of the **WordSet**, but the correctness is not guaranteed.

# Specific functionality
Some things I think will be useful to now: 1) the searching process in the internet is made by **python**'s library **BeautifulSoap**, 2) the *"conection"* between **Python** and **C++** is made by a file named *.defs.txt* that store the words finded(please don't remove it).

# Word Reference
In spite of be a little transparent, and for the sake of safety, I want to say that this is not an intent of made somthing harmful to the online dictionary. This is not a malitious bot. I don't realy now if there is a problem with the **WordReference** right's(I don't think so), but if there is, I will take off the repository.
