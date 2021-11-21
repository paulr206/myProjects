//
//  Tick_Tack_BombApp.swift
//  Tick Tack Bomb
//
//  Created by Paul on 23.05.21.
//

import SwiftUI

@main
struct Tick_Tack_BombApp: App {
    var body: some Scene {
        WindowGroup {
            startupView(coreDM: CoreDataManager())
        }
    }
}
