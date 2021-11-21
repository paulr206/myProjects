//
//  settingsView.swift
//  Tick Tack Boom
//
//  Created by Paul on 16.05.21.
//

import SwiftUI


struct settingsView: View {
    
    @State private var rounds = UserDefaults.standard.integer(forKey: "Rounds")
    let coreDM: CoreDataManager
    @State public var gamemodes: [Gamemode] = [Gamemode]()
    
    private func populateGamemodes() {
        gamemodes = coreDM.getAllGamemodes()
    }
    @State private var name: String = ""
    
    @State var gamemodesStruct: [GamemodeStruct]
    @State var needsRefresh: Bool
    
    var body: some View {
        
        VStack {
            VStack {
                Text("Einstellungen")
                    .font(.system(size: 25, weight: .bold))
                    .padding(10)
                
                Stepper("Runden: \((rounds == 0) ? 8 : rounds)", onIncrement: {
                    if (rounds < 12 && rounds >= 5) {
                        rounds += 1
                        UserDefaults.standard.set(rounds, forKey: "Rounds")
                    }
                    // if ist wenn App zum ersten Mal gestartet wird...
                    else if (rounds == 0) {
                        rounds = 9
                        UserDefaults.standard.set(rounds, forKey: "Rounds")
                    }
                    // wenn obere Grenze erreicht
                    else if (rounds == 12) {
                        rounds = 12
                    }
                }, onDecrement: {
                    if (rounds > 5 && rounds <= 12) {
                        rounds -= 1
                        UserDefaults.standard.set(rounds, forKey: "Rounds")
                    }
                    // if ist wenn App zum ersten Mal gestartet wird...
                    else if (rounds == 0) {
                        rounds = 7
                        UserDefaults.standard.set(rounds, forKey: "Rounds")
                    }
                    // wenn untere Grenze erreicht
                    else if (rounds == 5) {
                        rounds = 5
                    }
                })
                .padding()
                
                Spacer()
                
            }
            .offset(y:20)
            .background(Color.green1.edgesIgnoringSafeArea(.all))
        }
    }
    
    
    
    struct settingsView_Previews: PreviewProvider {
        static var previews: some View {
            settingsView(coreDM: CoreDataManager(), gamemodesStruct: [GamemodeStruct(name: "..", clicked: false, editable: true, modes: [])], needsRefresh: false)
        }
    }
    
}
