#ifndef MOVIETREE_HPP
#define MOVIETREE_HPP

#include <string>

struct MovieNode
{
    int ranking;
    std::string title;
    int year;
    int quantity;
    MovieNode *parent;
    MovieNode *leftChild;
    MovieNode *rightChild;

    MovieNode(){};

    MovieNode(int in_ranking, std::string in_title, int in_year, int in_quantity)
    {
        ranking = in_ranking;
        title = in_title;
        year = in_year;
        quantity = in_quantity;
        parent= NULL;
        leftChild=NULL;
        rightChild=NULL;
    }

};

class MovieTree
{
    public:
        MovieTree();
        ~MovieTree();
        void printMovieInventory();
        int countMovieNodes();
        void deleteMovieNode(std::string title);
        void addMovieNode(int ranking, std::string title, int releaseYear, int quantity);
        void findMovie(std::string title);
        void rentMovie(std::string title);

    protected:
    private:
		void DeleteAll(MovieNode* node);
        void printMovieInventory(MovieNode * node);
        void countMovieNodes(MovieNode* node, int *c);
        MovieNode* search(std::string title);
        MovieNode* treeMinimum(MovieNode* node);
        MovieNode *root;

};

#endif // MOVIETREE_HPP
