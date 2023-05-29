#pragma once
#include "..//Repo/repo.h"
#include <utility>
#include <vector>
#include <functional>
#include <fstream>

class ActionUndo{
public:
    virtual void doUndo() = 0;
    virtual ~ActionUndo() = default;
};

class UndoAdd: public ActionUndo{
    Offer offer;
    Repo_Offer* repo;
public:
    UndoAdd(const Offer& o, Repo_Offer *r) : offer{o}, repo{r}{}
    void doUndo() override{
        repo->remove(repo->find_pos(offer.get_name()));
    }
};

class UndoDelete: public ActionUndo{
    Offer offer;
    Repo_Offer* repo;
public:
    UndoDelete(const Offer& o, Repo_Offer *r) : offer{o}, repo{r}{}
    void doUndo() override{
        repo->add(offer);
    }
};

class UndoUpdate: public ActionUndo{
    Offer offer;
    Repo_Offer* repo;
public:
    UndoUpdate(const Offer& o, Repo_Offer *r): offer{o}, repo{r}{}
    void doUndo() override{
        repo->update(offer, repo->find_pos(offer.get_name()));
    }
};