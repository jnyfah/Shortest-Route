import logo from './logo.svg';
import './App.css';
import Autocomplete from './Autocomplete'
import cities from './cities';

function App() {
  return (
    <div className="App">
      
        <div className = "rowc">
          <div className ="source">
        <Autocomplete items = {cities}/>
        </div>
        <div className ="dest">
        <Autocomplete items = {cities}/>
        </div>

        <div className = "butn">
        <button> go</button>
        </div>

        
        </div>
     
    </div>
  );
}

export default App;
