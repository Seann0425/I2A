/* probID: W9-A2-Insertion */

// comment out the following line when submitting
struct node {
    char c;
    int pri, l_sz, r_sz;
    // pri, size of left child and right child
    node *lc, *rc, *p;
    // pointer to left child, right child, parent
};

void BST_insert_after(node *r, int pos, node *nde) {
    if (r->l_sz >= pos) {
        if (!r->lc) {
            r->lc = nde;
            nde->p = r;
        } else BST_insert_after(r->lc, pos, nde);
        r->l_sz++;
    } else {
        if (!r->rc) {
            r->rc = nde;
            nde->p = r;
        } else BST_insert_after(r->rc, pos - r->l_sz - 1, nde);
        r->r_sz++;
    }
}

void BST_insert_before(node *r, int pos, node *nde) {
    if (r->l_sz + 1 >= pos) {
        if (!r->lc) {
            r->lc = nde;
            nde->p = r;
        } else BST_insert_before(r->lc, pos, nde);
        r->l_sz++;
    } else {
        if (!r->rc) {
            r->rc = nde;
            nde->p = r;
        } else BST_insert_before(r->rc, pos - r->l_sz - 1, nde);
        r->r_sz++;
    }
}