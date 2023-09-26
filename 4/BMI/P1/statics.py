import os
from typing import List
from matplotlib import pyplot


def terms_stats(index):
    output_dir = "statics_pdfs/"
    collection = os.path.basename(index.index_path)
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    terms_freqs = index.all_terms_with_freq()
    terms_freqs.sort(key=lambda tup: tup[1], reverse=True)

    terms: List = []
    total_freqs: List = []
    for term in terms_freqs:
        terms.append(term[0])
        total_freqs.append(term[1])

    figure = pyplot.figure()
    pyplot.plot(terms, total_freqs)
    pyplot.xscale("log")
    pyplot.yscale("log")
    pyplot.xlabel("Terms frequency")
    pyplot.ylabel("Frequency of term in collection")
    pyplot.title("Term frequency in -> {}".format(collection))

    figure.savefig(os.path.join(output_dir, '{}_term_Freq.pdf'.format(collection)))

    all_terms = index.all_terms()
    doc_freqs: List = []

    for term in all_terms:
        doc_freqs.append((term, index.doc_freq(term)))
    doc_freqs.sort(key=lambda tup: tup[1], reverse=True)

    terms: List = []
    doc_freqs_list: List = []
    for term in doc_freqs:
        terms.append(term[0])
        doc_freqs_list.append(term[1])

    figure = pyplot.figure()
    pyplot.plot(terms, doc_freqs_list)
    pyplot.xscale("log")
    pyplot.yscale("log")
    pyplot.xlabel("Doc frequency")
    pyplot.ylabel("Docs with term")
    pyplot.title("Doc frequency in -> {}".format(collection))

    figure.savefig(os.path.join(output_dir, '{}_doc_Freq.pdf'.format(collection)))
