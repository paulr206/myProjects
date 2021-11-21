//
//  helpView.swift
//  Tick Tack Boom
//
//  Created by Paul on 16.05.21.
//

import SwiftUI

struct helpView: View {
    
    
    var body: some View {
        VStack {
            VStack {
                Text("Hilfe")
                    .font(.system(size: 25, weight: .bold))
                    .padding(10)
                
                Text("Hier soll die Hlfe stehen")
            }
            Spacer()
        }
        .offset(y:20)
    }
}



struct helpView_Previews: PreviewProvider {
    static var previews: some View {
        helpView()
    }
}
