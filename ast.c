#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "ast.h"
// LISTA
ast_node_list *new_list_node()
{
	ast_node_list *node = (ast_node_list *) malloc(sizeof(ast_node_list));
	node->length = 0;
	node->capacity = 16;
	node->list = (ast_node_sexp **) malloc(sizeof(ast_node_sexp *));
	return node;
}

void delete_list_node(ast_node_list *node)
{
	int i;
	for (i = 0; i < node->length; i++) {
		delete_sexp_node(node->list[i]);
	}
	free(node->list);
	free(node);
}

void add_node_to_list(ast_node_list *list, ast_node_sexp *node)
{
	if (list->length == list->capacity) {
		// TODO should allocate some more space
	}
	list->list[list->length] = node;
	list->length++;
}
void print_node_list(ast_node_list *node)
{
	int i = 0;
	printf("list node with %d elements\n", node->length);
	for (i = 0; i < node->length; i++) {
		print_node_sexp(node->list[i]);
	}
}
// FIN LISTA
// WHILE
ast_node_while *new_while_node(ast_cond_node *cond)
{
	ast_node_while *node = (ast_node_while *) malloc(sizeof(ast_node_while));
	node->length = 0;
	node->capacity = 16;
	node->cond = cond;
	node->wlist = (ast_node_sexp **) malloc(sizeof(ast_node_sexp *));
	return node;
}

void delete_while_node(ast_node_while *node)
{
	int i;
	for (i = 0; i < node->length; i++) {
		delete_sexp_node(node->wlist[i]);
	}
	free(node->wlist);
	free(node);
}

void add_node_to_while(ast_node_while *wlist, ast_node_sexp *node)
{
	if (wlist->length == wlist->capacity) {
		// TODO should allocate some more space
	}
	wlist->wlist[wlist->length] = node;
	wlist->length++;
}

void print_node_while(ast_node_while *node)
{
	int i = 0;
	printf("while node with %d elements and \"PRUEBA\" iterations\n", node->length);
	print_node_cond(node->cond);
	for (i = 0; i < node->length; i++) {
		print_node_sexp(node->wlist[i]);
	}
}

// FIN WHILE

// IF
ast_node_if *new_if_node(ast_cond_node *cond){
	ast_node_if *node = (ast_node_if *) malloc(sizeof(ast_node_if));
	node->length = 0;
	node->capacity = 16;
	node->cond = cond;
	node->iflist = (ast_node_sexp **) malloc(sizeof(ast_node_sexp *));

	return node;
}
void delete_if_node(ast_node_if *node){
	delete_atom_node(node->iflist);
	free(node);
}
void print_node_if(ast_node_if *node){
	int i = 0;
	printf("if node with %d elements \n", node->length);
	for (i = 0; i < node->length; i++) {
		print_node_sexp(node->iflist[i]);
	}
}
void add_node_to_if(ast_node_if *iflist, ast_node_sexp *node){
	if (iflist->length == iflist->capacity) {
		// TODO should allocate some more space
	}
	iflist->iflist[iflist->length] = node;
	iflist->length++;
}
// FIN IF

ast_node_atom *new_atom_node(enum atom_types type, void *v)
{
	ast_node_atom *node = (ast_node_atom *) malloc(sizeof(ast_node_atom));
	node->type = type;
	switch (type) {
		case AT_IDENTIFIER:
		case AT_STRING:
			node->value.string = (char *) malloc(strlen((char *) v)+1);
			strcpy(node->value.string, (char *) v);
			break;
		case AT_NUMBER:
			node->value.number = *((long *) v);
			break;
		case AT_FLOAT:
		node->value.flt = *((float *) v);
		break;
	}
	return node;
}

void delete_atom_node(ast_node_atom *node)
{
	switch (node->type) {
		case AT_IDENTIFIER:
		case AT_STRING:
			free(node->value.string);
			break;
		case AT_NUMBER:
			free(node->value.number);
			break;
		case AT_FLOAT:
			free((void *)&node->value.flt);
			break;	
	}
	free(node);
}

void print_node_atom(ast_node_atom *node)
{
	if (node->type == AT_IDENTIFIER) {
		printf("ID: %s\n", node->value.string);
	} else if (node->type == AT_STRING) {
		printf("STRING: %s\n", node->value.string);
	} else if (node->type == AT_NUMBER) {
		printf("INT: %ld\n", node->value.number);
	} else if (node->type == AT_FLOAT) {
		printf("FLOAT: %f\n", node->value.flt);
	} 
	
	else {
		printf("unknown atom node");
	}
}

ast_node_sexp *new_sexp_node(enum sexp_types type, void *v)
{
	ast_node_sexp *node = (ast_node_sexp *) malloc(sizeof(ast_node_sexp));

	node->type = type;
	switch (type) {
		case ST_ATOM:
			node->value.atom = (ast_node_atom *) v;
			break;
		case ST_LIST:
			node->value.list = (ast_node_list *) v;
			break;
		case ST_WHILE:
			node->value.wlist = (ast_node_while *) v;
			break;
		case ST_IF:
			node->value.iflist = (ast_node_if *) v;
			break;
		case ST_DECL:
			node->value.decl = (ast_node_decl *) v;
			break;
		case ST_ASSIGN:
			node->value.assign = (ast_node_assign *) v;
			break;
	}
	return node;
}

void delete_sexp_node(ast_node_sexp *node)
{
	switch (node->type) {
		case ST_ATOM:
			delete_atom_node(node->value.atom);
			break;
		case ST_LIST:
			delete_list_node(node->value.list);
			break;
		case ST_WHILE:
			delete_while_node(node->value.wlist);
			break;
		case ST_IF:
			delete_if_node(node->value.iflist);
			break;
		case ST_DECL:
			delete_decl_node(node->value.decl);
			break;
		case ST_ASSIGN:
			delete_assign_node(node->value.assign);
			break;
	}
	free(node);
}

void print_node_sexp(ast_node_sexp *node)
{
	if (node->type == ST_ATOM) {
		printf("node is an atom: ");
		print_node_atom(node->value.atom);
	} else if (node->type == ST_LIST) {
		printf("node is a list\n");
		print_node_list(node->value.list);
	} else if (node->type == ST_WHILE) {
		printf("node is a while\n");
		print_node_while(node->value.wlist);
		// print_node_cond(node->cond);
	} else if (node->type == ST_IF) {
		printf("node is a if\n");
		print_node_if(node->value.iflist);
		// print_node_cond(node->cond);
	} else if (node->type == ST_DECL) {
		printf("node is a declaration\n");
		print_node_decl(node->value.decl);
	} else if (node->type == ST_ASSIGN) {
		printf("node is an assign\n");
		print_node_assign(node->value.assign);
	} else {
		printf("node is a what?\n");
	}
}

// CONDICIONALES
ast_cond_node *new_cond_node(ast_node_atom *left, enum op_rel *op,  ast_node_atom *right){

	ast_cond_node *node = (ast_cond_node *) malloc(sizeof(ast_cond_node));
	node->left = left;
	node->op_rel = malloc(sizeof(enum op_rel));
	*node->op_rel = *op;
	node->right = right;
	return node;
}
void print_node_cond(ast_cond_node *node){
	printf("condition is :\n");
	print_node_atom(node->left);
	printf("OP_REL: %s\n", node->op_rel);
	print_node_atom(node->right);
}

void delete_cond_node(ast_cond_node *node) {
	delete_atom_node(node->left);
	delete_atom_node(node->right);
	free(node);
}

// DECL

ast_node_decl *new_decl_node(enum type type, const char *name){
	ast_node_decl *node = (ast_node_decl *) malloc(sizeof(ast_node_decl));
	node->type = type;
	node->name = name;
	return node;
}
void delete_decl_node(ast_node_decl *node){
	delete_atom_node(node->type);
	delete_atom_node(node->name);
	delete_atom_node(node->value);
	free(node);
}
void print_node_decl(ast_node_decl *node){
	printf("declaration node with type %d and name %s\n", node->type, node->name);
}
// FIN DECL

// ASSIGN

ast_node_assign *new_assign_node(const char *name, ast_node_atom *value){
	ast_node_assign *node = (ast_node_assign *) malloc(sizeof(ast_node_assign));
	node->type = value->type;
	node->name = name;
	node->value = value;
	return node;
}
void delete_assign_node(ast_node_assign *node){
	delete_atom_node(node->value);
	free(node);
}
void print_node_assign(ast_node_assign *node){
	printf("declaration node with type %d and name %s\n", node->type, node->name);
}
// FIN ASSIGN
