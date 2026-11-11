#pragma once
namespace visitanteDatos
{
constexpr float ReleaseTime = 6.8f, Duration = 13.5f;
struct KeyFrame { float time; Pose pose; float forward; glm::quat flowerRotation; };
const std::array<KeyFrame, 16> keyframes = {{
    // Flor en mano
    {0.0f,
        {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(0.0f, 0.0f, 0.0f), // torso
            glm::vec3(0.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(0.0f, 0.0f, 7.0f), // brazo_izq
            glm::vec3(-7.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(0.0f, 0.0f, -7.0f), // brazo_der
            glm::vec3(-7.0f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f},
        0.0f,
        glm::quat(1.0f, 0.0f, 0.0f, 0.0f)
    },
    // Espera inicial
    {0.8f,
        {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(0.0f, 0.0f, 0.0f), // torso
            glm::vec3(0.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(0.0f, 0.0f, 7.0f), // brazo_izq
            glm::vec3(-7.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(0.0f, 0.0f, -7.0f), // brazo_der
            glm::vec3(-7.0f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f},
        0.0f,
        glm::quat(1.0f, 0.0f, 0.0f, 0.0f)
    },
    // Reverencia
    {1.8f,
        {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(31.0f, 0.0f, 0.0f), // torso
            glm::vec3(-9.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-17.0f, 0.0f, 9.0f), // brazo_izq
            glm::vec3(-7.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-30.0f, 0.0f, -8.0f), // brazo_der
            glm::vec3(-32.0f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f},
        0.0f,
        glm::quat(1.0f, 0.0f, 0.0f, 0.0f)
    },
    // Descenso articulado
    {3.6f,
        {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(16.0f, 0.0f, 0.0f), // torso
            glm::vec3(4.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-17.0f, 0.0f, 8.0f), // brazo_izq
            glm::vec3(-34.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(-65.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(155.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(90.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-22.0f, 0.0f, -8.0f), // brazo_der
            glm::vec3(-39.0f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_der
            glm::vec3(-65.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(155.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(90.0f, 0.0f, 0.0f), // pie_der
        }}, -0.6451610923f},
        0.0f,
        glm::quat(1.0f, 0.0f, 0.0f, 0.0f)
    },
    // Recoger flor hacia el torso
    {4.3f,
        {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(16.0f, 0.0f, 0.0f), // torso
            glm::vec3(4.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-17.0f, 0.0f, 8.0f), // brazo_izq
            glm::vec3(-34.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(-65.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(155.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(90.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-22.0f, 0.0f, -8.0f), // brazo_der
            glm::vec3(-130.0f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_der
            glm::vec3(-65.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(155.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(90.0f, 0.0f, 0.0f), // pie_der
        }}, -0.6451610923f},
        0.0f,
        glm::quat(1.0f, 0.0f, 0.0f, 0.0f)
    },
    // Elevar flor antes de acercarla
    {4.9f,
        {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(31.0f, 0.0f, 0.0f), // torso
            glm::vec3(-9.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-5.0f, 0.0f, 8.0f), // brazo_izq
            glm::vec3(-100.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(-65.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(155.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(90.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-120.0f, 0.0f, 0.0f), // brazo_der
            glm::vec3(-40.0f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_der
            glm::vec3(-65.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(155.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(90.0f, 0.0f, 0.0f), // pie_der
        }}, -0.6451610923f},
        0.0f,
        glm::quat(1.0f, 0.0f, 0.0f, 0.0f)
    },
    // Brazo extendido y flor sobre la lapida
    {5.8f,
        {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(50.0f, 0.0f, 0.0f), // torso
            glm::vec3(-10.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-5.0f, 0.0f, 8.0f), // brazo_izq
            glm::vec3(-115.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(-65.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(155.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(90.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-171.4714767f, 0.0f, 0.0f), // brazo_der
            glm::vec3(34.70891208f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_der
            glm::vec3(-65.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(155.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(90.0f, 0.0f, 0.0f), // pie_der
        }}, -0.5751610994f},
        0.12f,
        glm::quat(0.5794549584f, 0.410672605f, -0.4068751931f, 0.5744847655f)
    },
    // Contacto y transferencia
    {6.8f,
        {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(50.0f, 0.0f, 0.0f), // torso
            glm::vec3(-10.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-5.0f, 0.0f, 8.0f), // brazo_izq
            glm::vec3(-115.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(-65.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(155.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(90.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-159.4714767f, 0.0f, 0.0f), // brazo_der
            glm::vec3(34.70891208f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_der
            glm::vec3(-65.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(155.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(90.0f, 0.0f, 0.0f), // pie_der
        }}, -0.5751610994f},
        0.12f,
        glm::quat(0.5794549584f, 0.410672605f, -0.4068751931f, 0.5744847655f)
    },
    // Pausa tras colocar
    {7.3f,
        {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(50.0f, 0.0f, 0.0f), // torso
            glm::vec3(-10.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-5.0f, 0.0f, 8.0f), // brazo_izq
            glm::vec3(-115.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(-65.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(155.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(90.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-159.4714767f, 0.0f, 0.0f), // brazo_der
            glm::vec3(34.70891208f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_der
            glm::vec3(-65.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(155.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(90.0f, 0.0f, 0.0f), // pie_der
        }}, -0.5751610994f},
        0.12f,
        glm::quat(0.5794549584f, 0.410672605f, -0.4068751931f, 0.5744847655f)
    },
    // Levantar mano libre
    {7.9f,
        {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(50.0f, 0.0f, 0.0f), // torso
            glm::vec3(-10.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-5.0f, 0.0f, 8.0f), // brazo_izq
            glm::vec3(-115.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(-65.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(155.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(90.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-171.4714767f, 0.0f, 0.0f), // brazo_der
            glm::vec3(34.70891208f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_der
            glm::vec3(-65.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(155.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(90.0f, 0.0f, 0.0f), // pie_der
        }}, -0.5751610994f},
        0.12f,
        glm::quat(0.5794549584f, 0.410672605f, -0.4068751931f, 0.5744847655f)
    },
    // Retraer mano por encima del borde
    {8.5f,
        {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(50.0f, 0.0f, 0.0f), // torso
            glm::vec3(-10.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-5.0f, 0.0f, 8.0f), // brazo_izq
            glm::vec3(-115.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(-65.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(155.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(90.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-180.0f, 0.0f, 0.0f), // brazo_der
            glm::vec3(-100.0f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_der
            glm::vec3(-65.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(155.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(90.0f, 0.0f, 0.0f), // pie_der
        }}, -0.6451610923f},
        0.1f,
        glm::quat(0.5394459367f, 0.4619719386f, -0.4577356577f, 0.5348441005f)
    },
    // Retirar brazo
    {9.3f,
        {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(16.0f, 0.0f, 0.0f), // torso
            glm::vec3(4.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-17.0f, 0.0f, 8.0f), // brazo_izq
            glm::vec3(-34.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(-65.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(155.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(90.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-22.0f, 0.0f, -8.0f), // brazo_der
            glm::vec3(-130.0f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_der
            glm::vec3(-65.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(155.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(90.0f, 0.0f, 0.0f), // pie_der
        }}, -0.6451610923f},
        0.0f,
        glm::quat(1.0f, 0.0f, 0.0f, 0.0f)
    },
    // Bajar mano fuera de la tumba
    {9.8f,
        {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(16.0f, 0.0f, 0.0f), // torso
            glm::vec3(4.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-17.0f, 0.0f, 8.0f), // brazo_izq
            glm::vec3(-34.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(-65.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(155.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(90.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-22.0f, 0.0f, -8.0f), // brazo_der
            glm::vec3(-39.0f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_der
            glm::vec3(-65.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(155.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(90.0f, 0.0f, 0.0f), // pie_der
        }}, -0.6451610923f},
        0.0f,
        glm::quat(1.0f, 0.0f, 0.0f, 0.0f)
    },
    // Regresar de rodillas
    {11.3f,
        {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(31.0f, 0.0f, 0.0f), // torso
            glm::vec3(-9.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(-17.0f, 0.0f, 9.0f), // brazo_izq
            glm::vec3(-7.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(-30.0f, 0.0f, -8.0f), // brazo_der
            glm::vec3(-32.0f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f},
        0.0f,
        glm::quat(1.0f, 0.0f, 0.0f, 0.0f)
    },
    // Postura inicial y flor depositada
    {13.0f,
        {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(0.0f, 0.0f, 0.0f), // torso
            glm::vec3(0.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(0.0f, 0.0f, 7.0f), // brazo_izq
            glm::vec3(-7.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(0.0f, 0.0f, -7.0f), // brazo_der
            glm::vec3(-7.0f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f},
        0.0f,
        glm::quat(1.0f, 0.0f, 0.0f, 0.0f)
    },
    // Estado final
    {13.5f,
        {{{
            glm::vec3(0.0f, 0.0f, 0.0f), // cadera
            glm::vec3(0.0f, 0.0f, 0.0f), // torso
            glm::vec3(0.0f, 0.0f, 0.0f), // cabeza
            glm::vec3(0.0f, 0.0f, 7.0f), // brazo_izq
            glm::vec3(-7.0f, 0.0f, 0.0f), // antebrazo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_izq
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_izq
            glm::vec3(0.0f, 0.0f, -7.0f), // brazo_der
            glm::vec3(-7.0f, 0.0f, 0.0f), // antebrazo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // mano_der
            glm::vec3(0.0f, 0.0f, 0.0f), // muslo_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pierna_der
            glm::vec3(0.0f, 0.0f, 0.0f), // pie_der
        }}, 1.490116119e-08f},
        0.0f,
        glm::quat(1.0f, 0.0f, 0.0f, 0.0f)
    },
}};
}
