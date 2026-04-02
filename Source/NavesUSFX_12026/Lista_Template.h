// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// 🔥 TEMPLATE (no lleva UCLASS)
template <typename T>
class Lista_Template
{
private:
    // 🔹 Nodo interno
    struct Nodo
    {
        T dato;
        Nodo* siguiente;

        Nodo(T valor) : dato(valor), siguiente(nullptr) {}
    };

    Nodo* cabeza;

public:
    // 🔹 Constructor
    Lista_Template() : cabeza(nullptr) {}

    // 🔹 Destructor (liberar memoria)
    ~Lista_Template()
    {
        Nodo* actual = cabeza;
        while (actual != nullptr)
        {
            Nodo* temp = actual;
            actual = actual->siguiente;
            delete temp;
        }
    }

    // 🔹 Insertar al final
    void Insertar(T valor)
    {
        Nodo* nuevo = new Nodo(valor);

        if (cabeza == nullptr)
        {
            cabeza = nuevo;
        }
        else
        {
            Nodo* temp = cabeza;
            while (temp->siguiente != nullptr)
            {
                temp = temp->siguiente;
            }
            temp->siguiente = nuevo;
        }
    }

    // 🔹 Obtener cabeza
    Nodo* GetCabeza()
    {
        return cabeza;
    }
};
