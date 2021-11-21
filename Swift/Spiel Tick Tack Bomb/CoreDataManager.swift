//
//  CoreDataManager1.swift
//  Tick Tack Bomb
//
//  Created by Paul on 23.05.21.
//

import Foundation
import CoreData

struct GamemodeStruct {
    var name: String
    var clicked: Bool
    var editable: Bool
    var modes: [String]
}

class CoreDataManager {
    
    let persistentContainer: NSPersistentContainer
    
    
    init() {
        persistentContainer = NSPersistentContainer(name: "MyDatamodel")
        persistentContainer.loadPersistentStores { (description, error) in
            if let error = error {
                fatalError("Core Data Store failed \(error.localizedDescription)")
            }
        }
        
    }
    
    func updateGamemode() {
        do {
            try persistentContainer.viewContext.save()
        } catch {
            persistentContainer.viewContext.rollback()
        }
    }
    
    
    func deleteGamemode(gamemode: Gamemode) {
        persistentContainer.viewContext.delete(gamemode)
        do {
            try persistentContainer.viewContext.save()
        } catch {
            persistentContainer.viewContext.rollback()
            print("Failed to safe context: \(error)")
        }
    }
    
    
    func getAllGamemodes() -> [Gamemode] {
        let fetchRequest: NSFetchRequest<Gamemode> = Gamemode.fetchRequest()
        
        do {
            return try persistentContainer.viewContext.fetch(fetchRequest)
        } catch {
            return []
        }
    }
    
    func getAllGamemodesAsStruct(classGamemode: [Gamemode]) -> [GamemodeStruct] {
        var modes: [GamemodeStruct] = []
        var i = 0
        if classGamemode.count > 0{
            for _ in 1...classGamemode.count {
                modes.append(GamemodeStruct(name: classGamemode[i].name!, clicked: classGamemode[i].clicked, editable: classGamemode[i].editable, modes: classGamemode[i].modes as! [String]))
                i = i + 1
            }
        }
        return modes
    }
    
    
    func saveGamemode(name: String, modes: [String], clicked: Bool, editable: Bool) {
        
        let gamemode = Gamemode(context: persistentContainer.viewContext)
        gamemode.name = name
        gamemode.modes = modes as NSObject
        gamemode.clicked = clicked
        gamemode.editable = editable
        
        do {
            try persistentContainer.viewContext.save()
        } catch {
            print("Failed to save gamemode \(error)")
        }
        
    }
    
}

