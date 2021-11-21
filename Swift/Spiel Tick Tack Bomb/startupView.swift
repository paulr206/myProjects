//
//  startupView.swift
//  Tick Tack Boom
//
//  Created by Paul on 01.05.21.
//

import SwiftUI


    
//Farbe und Images
var unselectedColor: UIColor = .systemYellow
var unselectedIcon: String = "circle"
var selectedColor: UIColor = .systemOrange
var selectedIcon: String = "checkmark.circle.fill"


struct startupView: View {
    
    @State private var isFirstStart = UserDefaults.standard.bool(forKey: "FirstStart")
    
    // Darkmode oder Lightmode
    @Environment(\.colorScheme) var colorScheme: ColorScheme
    
    let coreDM: CoreDataManager
    @State public var gamemodes: [Gamemode] = []
    @State private var gamemodesStruct: [GamemodeStruct] = []
    @State private var playerStruct: [PlayerStruct] = []
    @State private var needsRefresh: Bool = false
    
    @State private var settingsArePresented: Bool = false
    @State private var helpIsPresented: Bool = false
    @State private var playerIsPresented: Bool = false
    @State private var gamemodeIsPresented: Bool = false
    @State private var gameIsPresented: Bool = false
    @State private var noModeSelected: Bool = false
    
    var body: some View {
        
        NavigationView {
            // Stack der ganzen Ansicht
            VStack {
                
                /*
                                    Header + Bombenbild
                */
                
                // Stack des Headers
                VStack {
                    // Stack Buttons + Titel
                    HStack {
                        // Help Button
                        Button(action: {
                            helpIsPresented.toggle()
                        }, label: {
                            Image(systemName: "questionmark.circle.fill")
                                .font(.system(size: 20, weight: .bold))
                                .foregroundColor(colorScheme == .dark ? .white : .black)
                        })
                        .padding(10)
                        .sheet(isPresented: $helpIsPresented){
                            helpView()
                        }
                        
                        Spacer()
                        
                        Text("Tick Tack Boom")
                            .font(.system(size: 25, weight: .bold))
                            .padding(10)
                        
                        Spacer()
                        
                        // Settings
                        Button(action: {
                            settingsArePresented.toggle()
                        }, label: {
                            Image(systemName: "gearshape.fill")
                                .font(.system(size: 20, weight: .bold))
                                .foregroundColor(colorScheme == .dark ? .white : .black)
                        })
                        .padding(10)
                        .sheet(isPresented: $settingsArePresented){
                            settingsView(coreDM: coreDM, gamemodesStruct: gamemodesStruct, needsRefresh: false)
                        }
                        
                    }
                    Image("bomb-emoji")
                        .resizable()
                        .frame(width: 110, height: 110)
                }
                
                /*
                                                Main Bereich
                */
                
                VStack{
                        ScrollView(){
                            
                            HStack {
                                Text("Spielmodis")
                                    .font(.title).bold()
                                Spacer()
                                Text("hinzufügen")
                                    .onTapGesture {
                                        gamemodeIsPresented.toggle()
                                    }
                                    .fullScreenCover(isPresented: $gamemodeIsPresented){
                                        gamemodeView(coreDM: coreDM)
                                    }
                                    
                            }
                                .padding()
                            
                            // Spielmodis
                            ScrollView(.horizontal, showsIndicators: false) {
                                HStack {
                                    ForEach(0..<gamemodesStruct.count) { index in
                                        GeometryReader { geometry in
                                            if index <= gamemodesStruct.count {
                                            
                                               // Cards
                                                VStack {
                                                    Text("\(gamemodesStruct[index].name)")
                                                        .font(.title).bold()
                                                        .foregroundColor(.black)
                                                        .shadow(radius: 10)
                                                }
                                                .frame(width: 150, height: 200)
                                                .onTapGesture {
                                                    gamemodesStruct[index].clicked.toggle()
                                                    //gamemodes = coreDM.getAllGamemodes()
                                                    print("Modus \(gamemodesStruct[index].clicked)")
                                                }
                                                .background((gamemodesStruct[index].clicked) ? Color.green2 : Color.green3)
                                                .cornerRadius(20)
                                                .shadow(color: (gamemodesStruct[index].clicked) ? Color.green2.opacity(0.3) : Color.green3.opacity(0.3), radius: 20, x: 0, y: 10)
                                                .shadow(color: (gamemodesStruct[index].clicked) ? Color.green2.opacity(0.3) : Color.green3.opacity(0.3), radius: 5, x: 0, y: 2)
                                            }
                                            
                                        }
                                        .frame(width: 150, height: 220)
                                }
                                    
                                }
                                .padding(10)
                            }
                            
                            HStack {
                                Text("Spieler")
                                    .font(.title).bold()
                                Spacer()
                                Text("hinzufügen")
                                    .onTapGesture {
                                        playerIsPresented.toggle()
                                    }
                                    .fullScreenCover(isPresented: $playerIsPresented){
                                        playerView(coreDM: coreDM)
                                    }
                            }
                                .padding()
                            
                            
                            // Spieler
                            ScrollView(.horizontal, showsIndicators: false) {
                                HStack {
                                    ForEach(0..<gamemodesStruct.count) { index in
                                        GeometryReader { geometry in
                                            if index <= gamemodesStruct.count {
                                            
                                               // Cards
                                                VStack {
                                                    Text("\(gamemodesStruct[index].name)")
                                                        .font(.title).bold()
                                                        .foregroundColor(.black)
                                                        .shadow(radius: 10)
                                                }
                                                .frame(width: 150, height: 200)
                                                .onTapGesture {
                                                    gamemodesStruct[index].clicked.toggle()
                                                    //gamemodes = coreDM.getAllGamemodes()
                                                    print("Modus \(gamemodesStruct[index].clicked)")
                                                }
                                                .background((gamemodesStruct[index].clicked) ? Color.green2 : Color.green3)
                                                .cornerRadius(20)
                                                .shadow(color: (gamemodesStruct[index].clicked) ? Color.green2.opacity(0.3) : Color.green3.opacity(0.3), radius: 20, x: 0, y: 10)
                                                .shadow(color: (gamemodesStruct[index].clicked) ? Color.green2.opacity(0.3) : Color.green3.opacity(0.3), radius: 5, x: 0, y: 2)
                                            }
                                            
                                        }
                                        .frame(width: 150, height: 220)
                                }
                                    
                                }
                                .padding(10)
                            }
                            
                        }
                        // accentColor nur zur aktualisierung, damit needsRefresh benutzt wird
                        .accentColor(needsRefresh ? .clear : .clear)
                        .onAppear(){
                            UITableView.appearance().backgroundColor = UIColor.clear
                            UITableViewCell.appearance().backgroundColor = UIColor.clear
                        }
                        .padding()
                         
                }
                
                /*
                                        Footer mit StartButton
                */
                
                VStack {
                    if noModeSelected {
                        Text("Spielmodis hinzufügen!")
                            .offset(y: -10)
                            .animation(.easeIn)
                    }
                    Image(systemName: "arrow.right")
                        .padding(.init(top: 20, leading: 40, bottom: 20, trailing: 40))
                        .background(Color.green3)
                        .cornerRadius(50)
                        .foregroundColor(colorScheme == .dark ? .white : .black)
                        .font(.system(size: 20, weight: .bold))
                        .offset(y: -10)
                        .onTapGesture {
                            if gamemodes.count > 0 {
                                gameIsPresented.toggle()
                            }
                            else {
                                noModeSelected = true
                            }
                        }
                        .fullScreenCover(isPresented: $gameIsPresented) {
                            gameView()
                        }
                }
                
            }
            .background(Color.green1.edgesIgnoringSafeArea(.all))
            .onAppear(){
                /*if isFirstStart {
                    fullScreenCover(isPresented: $isFirstStart){
                        gamemodeView(coreDM: coreDM)
                    }
                }*/
                gamemodes = coreDM.getAllGamemodes()
                gamemodesStruct = coreDM.getAllGamemodesAsStruct(classGamemode: gamemodes)
            }
           
        .navigationBarHidden(true)
    }
}


func selectedModes(arrayOfModes: [GamemodeStruct]) -> [GamemodeStruct] {
    var selected: [GamemodeStruct] = []
    var i = 0
    if arrayOfModes.count > 0{
        for _ in 1...arrayOfModes.count {
            if (arrayOfModes[i].clicked == true) {
                selected.append(arrayOfModes[i])
            }
            i = i + 1
        }
    }
    return selected
}


func isDarkMode(mode: ColorScheme) -> Bool {
    if(mode == .dark) {
        return true
    }
    else {
        return false
    }
}







struct startupView_Previews: PreviewProvider {
    static var previews: some View {
        startupView(coreDM: CoreDataManager())
    }
}

}
