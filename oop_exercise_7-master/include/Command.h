#ifndef COMMAND_H
#define COMMAND_H

#include <fstream>
#include <vector>
#include <deque>
#include <memory>
#include <string>

#include "Shape.h"
#include "Factory.h"

class commander_error : public std::logic_error {
public:
    commander_error(std::string const& msg) : std::logic_error(msg)
    {}
};

template <class T>
class Command;
template <class T>
class CommandManager{
public:

    CommandManager(std::vector< std::shared_ptr<Shape<T>> >& vec) : shapes(vec) { }

    void add(std::shared_ptr< Command<T> > comm)
    {
        comm->execute();
        listOfComm.erase(listOfComm.begin() + currentCommand, listOfComm.end());
        listOfComm.push_back(comm);
        ++currentCommand;
    }

    void undo()
    {
        if (currentCommand == 0) throw commander_error("No operations to undo");
        --currentCommand;
        listOfComm[currentCommand]->undo();
        std::cout << "Commander: Undid " << listOfComm[currentCommand]->getCommName() << "\n";
    }

    void redo()
    {
        if (currentCommand == listOfComm.size()) throw commander_error("No operations to redo");
        listOfComm[currentCommand]->execute();
        std::cout << "Commander: Redid " << listOfComm[currentCommand]->getCommName() << "\n";
        ++currentCommand;
    }

    void reload()
    {
        listOfComm.clear();
        shapes.clear();
        currentCommand = 0;
    }

    void save()
    {
        std::string filePath;
        std::ofstream outfile;

        std::cout << "Save path: ";
        std::cin  >> filePath;
        
        outfile.open(filePath, std::ios::out);
        if (outfile.fail())
        {
            throw std::runtime_error("File open operation failed");
        }

        std::vector< std::pair<T,T> > points;
        outfile << shapes.size() << '\t';
        for(std::shared_ptr<Shape<T>> e : shapes)
        {
            points = e->getPoints();
            outfile << e->getType() << '\t';
            switch(e->getType())
            {
                case 0:
                    for (int i = 0; i < 3; ++i)
                    {
                        outfile << points[i].first << '\t' << points[i].second << '\t';
                    }
                    break;
                
                case 1:

                case 2:
                    for (int i = 0; i < 4; ++i)
                    {
                        outfile << points[i].first << '\t' << points[i].second << '\t';
                    }
                    break;
            }
        }
        outfile.close();
    }
    
    void load()
    {
        std::string filePath;
        std::ifstream infile;
        char ch;

        std::cout << "Any unsaved changes will be lost. Continue? (y/n): ";
        do {
            std::cin >> ch;
            if (ch == 'y') { ; }
            else if (ch == 'n') { return; }
            else
            {
                std::cout << "(y/n): ";
            }
        } while (ch != 'y');

        std::cout << "Load path: ";
        std::cin  >> filePath;
        
        infile.open(filePath, std::ios::in);
        if (infile.fail())
        {
            throw std::runtime_error("File open operation failed");
        }

        reload();

        int size, type;
        std::pair<T, T> p[4];

        infile >> size;
        for (int i = 0; i < size; ++i)
        {
            infile >> type;
            switch (type)
            {
                case 0:
                    for (int j = 0; j < 3; ++j)
                    {
                        infile >> p[j].first >> p[j].second;
                    }
                    break;

                case 1:

                case 2:
                    for (int j = 0; j < 4; ++j)
                    {
                        infile >> p[j].first >> p[j].second;
                    }
                    break;
            }
            shapes.push_back(Factory<T>::create(type, p));
        }
    }
private:
    int currentCommand = 0;
    std::vector< std::shared_ptr<Shape<T>> >& shapes;
    std::deque< std::shared_ptr<Command<T>> > listOfComm;
};

template <class T>
class Command{
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    std::string getCommName() const
    { return commName; }

protected:
    typedef std::pair<T, T> Point;
    std::string commName = "Undefined";
};

template <class T>
class Add : public Command<T> {
public:
    using typename Command<T>::Point;
    using Command<T>::commName;

    Add(std::vector< std::shared_ptr<Shape<T>> >& vec, int type, Point (&points)[4]) :
        shapes(vec), shapeType(type), p(points) { commName = "Add"; }

    void execute() override
    {
        shapes.push_back(Factory<T>::create(shapeType, p));
    }

    void undo() override
    {
        shapes.pop_back();
    }
private:
    int shapeType;
    Point p[4];
    std::vector< std::shared_ptr<Shape<T>> >& shapes;
};

template <class T>
class Delete : public Command<T> {
public:
    using typename Command<T>::Point;
    using Command<T>::commName;

    Delete(std::vector< std::shared_ptr<Shape<T>> >& vec, int num) : shapes(vec), pos(num)
    {
        commName = "Delete";

        std::vector< std::pair<T, T> > points;
        points = vec[num]->getPoints();
        shapeType = vec[num]->getType();
        switch(shapeType)
        {
            case 0:
                for (int i = 0; i < 3; ++i)
                {
                    p[i] = points[i];
                }
                break;
            case 1:

            case 2:
                for (int i = 0; i < 4; ++i)
                {
                    p[i] = points[i];
                }
                break;
        }
    }

    void execute()
    {
        shapes.erase(shapes.begin() + pos);
    }

    void undo()
    {
        shapes.insert(shapes.begin() + pos, Factory<T>::create(shapeType, p));
    }

private:
    int pos;
    int shapeType;
    Point p[4];
    std::vector< std::shared_ptr<Shape<T>> >& shapes;
};


#endif