//
//  playerView.swift
//  Tick Tack Boom
//
//  Created by Paul on 08.05.21.
//

import SwiftUI

struct PlayerStruct {
    var name: String
    var id: Int
    var clicked: Bool
}


struct playerView: View {
    let coreDM: CoreDataManager
    // darmode?
    @Environment(\.colorScheme) var colorScheme
    // zum Zeigen von gameView
    @State private var startupIsPresented = false
    // zum Zeigen von editPlayerView
    @State private var editPlayerIsPresented = false
    @State private var rounds = UserDefaults.standard.integer(forKey: "Rounds")
    @State private var name = ""
    
    // DATEN
    @State var player: [PlayerStruct] = []
    
    let screenWidth = UIScreen.main.bounds.size.width
    
    var body: some View {
        NavigationView {
            VStack {
                HStack {
                    /*Image(systemName: "minus")
                        .padding(10)*/
                    
                    Spacer()
                    
                    Text("Spieler")
                        .font(.system(size: 25, weight: .bold))
                        .padding(10)
                    
                    Spacer()
                    
                    /*Image(systemName: "plus")
                        .padding(10)
                        .onTapGesture {
                            editPlayerIsPresented.toggle()
                        }
                        .fullScreenCover(isPresented: $editPlayerIsPresented) {
                            editPlayerView()
                        }*/
                    
                }
                
                // Spieler hinzufügen
                VStack {
                    TextField("Name eingeben", text: $name)
                        .disableAutocorrection(true)
                        .padding()
                        .frame(width: screenWidth-20, height: 50, alignment: .center)
                        .background(Color.green3)
                        .cornerRadius(20)
                    Button("hinzufügen", action: {
                        player.append(PlayerStruct(name: name, id: player.count+1, clicked: true))
                        name = ""
                    })
                    .foregroundColor(.green3)
                }
                .padding(.top, 50)
                
                Spacer()
                
                if(player.isEmpty) {
                    Text("Keine Spieler")
                }
                else {
                    List {
                        ForEach(0..<player.count) { index in
                            HStack {
                                VStack {
                                    Text("Auswahl \(player[index].id)")
                                    Text("\(player[index].name)")
                                }
                                .padding()
                                .frame(minWidth: 0, idealWidth: 100, maxWidth: .infinity, minHeight: 70, idealHeight: 70, maxHeight: .infinity, alignment: .center)
                                .background((player[index].clicked == true) ? Color(selectedColor) : Color(unselectedColor))
                                .cornerRadius(25)
                                .onTapGesture {
                                    player[index].clicked.toggle()
                                }
                                
                                Image(systemName: (player[index].clicked == true) ? selectedIcon : unselectedIcon)
                                    .font(.system(size: 20, weight: .bold))
                                    .padding(5)
                                    .foregroundColor((isDarkMode(mode: colorScheme)) ? .white : .black)
                            }
                        }
                    }
                }
                Spacer()

                
                Image(systemName: "arrow.right")
                    .padding(.init(top: 20, leading: 40, bottom: 20, trailing: 40))
                    .background(Color.green3)
                    .cornerRadius(50)
                    .foregroundColor(colorScheme == .dark ? .white : .black)
                    .font(.system(size: 20, weight: .bold))
                    .offset(y: -20)
                    .onTapGesture {
                        // erster Start der App
                        if(rounds == 0) {
                            rounds = 8
                            UserDefaults.standard.set(rounds, forKey: "Rounds")
                        }
                        startupIsPresented.toggle()
                    }
                    .fullScreenCover(isPresented: $startupIsPresented) {
                        startupView(coreDM: coreDM)
                    }
            }
            .navigationBarHidden(true)
            .navigationBarBackButtonHidden(true)
            .background(Color.green1.edgesIgnoringSafeArea(.all))
            
        }
        
    }
    
    func isDarkMode(mode: ColorScheme) -> Bool {
        if(mode == .dark) {
            return true
        }
        else {
            return false
        }
    }
    
    
}


struct playerView_Previews: PreviewProvider {
    static var previews: some View {
        playerView(coreDM: CoreDataManager())
    }
}
