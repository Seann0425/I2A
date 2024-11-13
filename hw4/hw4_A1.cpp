/* probID: W9-A1-Rotation */

// remember to comment out the following line when submitting
struct node {
    char c;
    int pri, l_sz, r_sz;
    // pri, size of left child and right child
    node *lc, *rc, *p;
    // pointer to left child, right child, parent
};

node *rotate_dir(node *r, bool dir) {
    if (!r) return nullptr;
    node *new_one = nullptr;
    if (dir) {
        // right roration
        new_one = r->lc;
        if (!new_one) return r;
        r->lc = new_one->rc;
        if (new_one->rc) new_one->rc->p = r;
        new_one->rc = r;
        new_one->p = r->p;
        r->p = new_one;
        r->l_sz = new_one->r_sz;
        new_one->r_sz += r->r_sz + 1;
        if (new_one->p) {
            if (new_one->p->lc == r) new_one->p->lc = new_one;
            else new_one->p->rc = new_one;
        }
    } else {
        // left rotation
        new_one = r->rc;
        if (!new_one) return r;
        r->rc = new_one->lc;
        if (new_one->lc) new_one->lc->p = r;
        new_one->lc = r;
        new_one->p = r->p;
        r->p = new_one;
        r->r_sz = new_one->l_sz;
        new_one->l_sz += r->l_sz + 1;
        if (new_one->p) {
            if (new_one->p->lc == r) new_one->p->lc = new_one;
            else new_one->p->rc = new_one;
        }
    }
    return new_one;
}