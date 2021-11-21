//
//  gameView.swift
//  Tick Tack Boom
//
//  Created by Paul on 16.05.21.
//

import SwiftUI

struct gameView: View {
    
    @State private var rounds = UserDefaults.standard.integer(forKey: "Rounds")
    
    var body: some View {
        VStack {
            Text("Game")
            Text("Es werden \(rounds) Runden gespielt")
        } 
    }
}



struct gameView_Previews: PreviewProvider {
    static var previews: some View {
        gameView()
    }
}
