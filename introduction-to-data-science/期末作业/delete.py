def delblankline(infile,outfile):
    infp=open(infile,"r")
    outfp=open(outfile,"w")
    lines=infp.readlines()
    for li in lines:
        if li.split():
            outfp.writelines(li)
    infp.close()
    outfp.close()

delblankline("pred2.txt","pred2_.txt")