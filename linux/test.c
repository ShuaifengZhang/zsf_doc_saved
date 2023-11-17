static struct rb_root my_rb_root = RB_ROOT;

struct my_data {
    int key;
    char value;
};

struct my_data *my_data_alloc(void) {
    return kzalloc(sizeof(*my_data), GFP_KERNEL);
}

void my_data_free(struct my_data *data) {
    kfree(data);
}

static int my_compare(struct rb_node *node1, struct rb_node *node2) {
    struct my_data *key1 = container_of(node1, struct my_data, node);
    struct my_data *key2 = container_of(node2, struct my_data, node);

    return key1->key - key2->key;
}

static void my_print(struct rb_node *node) {
    struct my_data *data = container_of(node, struct my_data, node);
    printk(KERN_INFO "Key: %d, Value: %c
", data->key, data->value);
}

static void __init my_init(void) {
    int i;
    for (i = 0; i < 10; i++) {
        struct my_data *data = my_data_alloc();
        if (!data) {
            printk(KERN_ERR "Failed to allocate memory for data
");
            return;
        }
        data->key = i;
        data->value = 'A' + i;
        rb_insert(&my_rb_root, &data->node, my_compare);
    }

    rbtree_preorder_traversal(&my_rb_root, my_print, NULL);
}

static void __exit my_exit(void) {
    rbtree_inorder_traversal(&my_rb_root, my_print, NULL);
}