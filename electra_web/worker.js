import createModule from "./electra.js";

let Electra = null;
let input = null;
let code = null;
let last_output = '';

onmessage = async (e) => {
  let {type, data} = e.data;

  if(type === "start") {
    code = data.code;
    input = data.input;

    if(!Electra) {
      Electra = await createModule();
    }

    loop();
  }
};

function loop() {
  Electra.init(input);
  Electra.set_source_code(code);
  Electra.generate();
  Electra.step();

  while(Electra.has_currents()) {
    Electra.step();
    const output = Electra.get_output();

    if(output !== last_output) {
      last_output = output;
      postMessage({ type: "output", data: output });
    }
  }
  postMessage({ type: "final", data: "\n[Program finished]\n" });
}
