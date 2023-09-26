class Index:
    def __init__(self, path):
        pass

    def doc_vector(self, doc_id):
        pass

    def ndocs(self):
        pass

    def all_terms(self):
        pass

    def all_terms_with_freq(self):
        pass

    def total_freq(self, term):
        pass

    def doc_path(self, id):
        pass

    def term_freq(self, term, id):
        pass

    def doc_freq(self, term):
        pass

    def postings(self, term):
        pass


class Builder:
    def __init__(self):
        pass

    def build(collection):
        pass

    def commit(self):
        pass
