//
//  gamemodeView.swift
//  Tick Tack Bomb
//
//  Created by Paul on 30.05.21.
//

import SwiftUI

struct gamemodeView: View {
    let coreDM: CoreDataManager
    @State public var gamemodes: [Gamemode] = []
    
    @State private var gamemodeName = ""
    
    
    @State private var startupIsPresented: Bool = false
    @Environment(\.colorScheme) var colorScheme
    let screenWidth = UIScreen.main.bounds.size.width
    
    var body: some View {
        NavigationView{
            VStack{
                HStack{
                    Spacer()
                    Text("Spielmodis")
                        .font(.system(size: 25, weight: .bold))
                        .padding(10)
                    Spacer()
                }
                VStack {
                    TextField("Spielmodus Aufgabe", text: $gamemodeName)
                        .disableAutocorrection(true)
                        .padding()
                        .frame(width: screenWidth-20, height: 50, alignment: .center)
                        .background(Color.green3)
                        .cornerRadius(20)
                    Button("hinzufügen", action: {
                        coreDM.saveGamemode(name: gamemodeName, modes: ["a", "b"], clicked: false, editable: true)
                        gamemodeName = ""
                        gamemodes = coreDM.getAllGamemodes()
                    })
                    .foregroundColor(.green3)
                }
                
                Spacer()
                
                List(gamemodes) {object in 
                    Text("Hallo")
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
                        startupIsPresented.toggle()
                    }
                    .fullScreenCover(isPresented: $startupIsPresented) {
                        startupView(coreDM: coreDM)
                    }
            }
            .onAppear(){
                gamemodes = coreDM.getAllGamemodes()
            }
            .background(Color.green1.edgesIgnoringSafeArea(.all))
            .navigationBarHidden(true)
        }
    }
}

struct gamemodeView_Previews: PreviewProvider {
    static var previews: some View {
        gamemodeView(coreDM: CoreDataManager())
    }
}
